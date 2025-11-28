#include <GUI/Container.hpp>
#include <SDL3/SDL_log.h>
#include <cmath>
#include <cstdlib>

bool point_within_rect(double x, double y, SDL_FRect rect) {
  return x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h;
}

GUIContainer::GUIContainer(std::string tag) : tag(tag) {}

GUIContainer::GUIContainer(std::string tag, GUILayout layout)
    : tag(tag), layout(layout) {}

void GUIContainer::on_resize(double parent_width, double parent_height) {
  int old_w = rect.w, old_h = rect.h;
  rect = layout.calculate(parent_width, parent_height);

  /* Adjust min. size */
  if (rect.w < min_width.to_pixels(parent_width))
    rect.w = min_width.to_pixels(parent_width);
  if (rect.h < min_height.to_pixels(parent_height))
    rect.h = min_height.to_pixels(parent_height);

  if (rect.w != old_w || rect.h != old_h)
    cache_is_outdated = true;

  for (GUIContainer *child : children)
    child->on_resize(rect.w, rect.h);

  /* Re-check mouse position */
  reset_mouse();
}

void GUIContainer::set_skin(Skin *new_skin) {
  this->skin = new_skin;
  cache_is_outdated = true;
}

void GUIContainer::set_cursor(SDL_Cursor *cursor) { this->cursor = cursor; }

void GUIContainer::set_min_width(GUIUnit min_width) {
  this->min_width = min_width;
}

void GUIContainer::set_min_height(GUIUnit min_height) {
  this->min_height = min_height;
}

void GUIContainer::set_draggable(bool draggable) { is_draggable = draggable; }

SDL_FRect GUIContainer::get_bounding_rect() const { return rect; }

void GUIContainer::move(double dx, double dy) {
  SDL_Log("Moving %f %f", dx, dy);
  rect.x += dx;
  rect.y += dy;
}

double GUIContainer::get_width() const { return rect.w; }
double GUIContainer::get_height() const { return rect.h; }
bool GUIContainer::is_mouse_over() const { return mouse_over; };
bool GUIContainer::is_mouse_down() const { return mouse_down; };

void GUIContainer::add_container(GUIContainer *container) {
  children.push_back(container);
  children.back()->on_resize(rect.w, rect.h);
}

void GUIContainer::add_text(GUIText *text) { texts.push_back(text); }

void GUIContainer::update_cache(SDL_Renderer *renderer) {
  if (cache != NULL)
    SDL_DestroyTexture(cache);
  cache =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
                        SDL_TEXTUREACCESS_TARGET, round(rect.w), round(rect.h));
  SDL_SetRenderTarget(renderer, cache);

  if (mouse_down)
    skin->render({0, 0, rect.w, rect.h}, Active);
  else if (mouse_over)
    skin->render({0, 0, rect.w, rect.h}, Hover);
  else
    skin->render({0, 0, rect.w, rect.h}, Base);

  for (GUIText *text : texts)
    text->render(renderer, rect.w, rect.h);
  SDL_SetRenderTarget(renderer, NULL);
  cache_is_outdated = false;
}

std::vector<GUIContainer *> GUIContainer::get_children(double x, double y) {
  std::vector<GUIContainer *> result;
  for (GUIContainer *child : children) {
    const SDL_FRect rect = child->get_bounding_rect();
    if (point_within_rect(x, y, rect))
      result.push_back(child);
  }
  return result;
}

void GUIContainer::on_mouse_enter(double x, double y) {
  SDL_Log("Mouse enter %f %f %f %f from %f %f", rect.x, rect.y, rect.w, rect.h,
          x, y);
  mouse_over = true;
  cache_is_outdated = true;
  if (cursor) {
    // SDL_Log("Setting cursor");
    SDL_SetCursor(cursor);
  }
}

void GUIContainer::on_mouse_leave() {
  for (GUIContainer *child : children)
    child->on_mouse_leave();
  if (!mouse_over)
    return;
  SDL_Log("Mouse leave %f %f %f %f", rect.x, rect.y, rect.w, rect.h);
  // mouse_down = false;
  if (cursor) {
    SDL_SetCursor(SDL_GetDefaultCursor());
    // SDL_Log("Clearing cursor");
  }
  mouse_over = false;
  cache_is_outdated = true;
}

bool GUIContainer::on_mouse_down(double x, double y) {
  // SDL_Log("Mouse down %f %f %f %f %b", rect.x, rect.y, rect.w, rect.h,
  // is_draggable);
  std::vector<GUIContainer *> child = get_children(x, y);
  if (!child.empty())
    return child.back()->on_mouse_down(x, y);
  else {
    mouse_down = true;
    cache_is_outdated = true;
    return is_bubbling;
  }
}

void GUIContainer::on_mouse_up(double x, double y) {
  std::vector<GUIContainer *> child = get_children(x, y);
  for (GUIContainer *child : children)
    child->on_mouse_up(x, y);

  if (!mouse_down)
    return;
  SDL_Log("Mouse up %f %f %f %f", rect.x, rect.y, rect.w, rect.h);

  if (child.empty() && mouse_over && mouse_down)
    on_mouse_click();

  if (mouse_dragging) {
    SDL_Log("Stoped dragging");
    mouse_dragging = false;
  }

  mouse_down = false;
  cache_is_outdated = true;
}

void GUIContainer::on_mouse_click() {
  SDL_Log("Mouse click %f %f %f %f", rect.x, rect.y, rect.w, rect.h);
}

void GUIContainer::on_mouse_move(double x1, double y1, double x2, double y2) {
  // SDL_Log("Mouse move %f %f %f %f", rect.x, rect.y, rect.w, rect.h);
  // SDL_Log("%f %f %f %f", x1, y1, x2, y2);
  std::vector<GUIContainer *> child1 = get_children(x1, y1);
  std::vector<GUIContainer *> child2 = get_children(x2, y2);

  if (mouse_down && !mouse_dragging) {
    mouse_dragging = true;
    SDL_Log("Started dragging %s", tag.c_str());
  }

  if (!child1.empty() && mouse_dragging) {
    child1.back()->move(x2 - x1, y2 - y1);
    child1 = get_children(x1, y1);
    child2 = get_children(x2, y2);
  }

  /* No children involved */
  if (child1.empty() && child2.empty()) {
    return;
  }

  /* Mouse within one child */
  if (!child1.empty() && !child2.empty() && child1.back() == child2.back()) {
    child1.back()->on_mouse_move(x1, y1, x2, y2);
    return;
  }

  /* Entered child2 */
  if (!child2.empty()) {
    on_mouse_leave();
    child2.back()->on_mouse_enter(x2, y2);
  }

  /* Left child1 */
  if (!child1.empty()) {
    child1.back()->on_mouse_leave();
    if (child2.empty())
      on_mouse_enter(x2, y2);
  }
}

void GUIContainer::reset_mouse() {
  SDL_Log("Resetting mouse");
  float x = 0, y = 0;
  SDL_GetMouseState(&x, &y);

  std::vector<GUIContainer *> children = get_children(x, y);
  if (children.empty()) {
    if (point_within_rect(x, y, rect) && !mouse_over)
      on_mouse_enter(x, y);
    if (!point_within_rect(x, y, rect) && mouse_over)
      on_mouse_leave();
  } else
    children.back()->reset_mouse();
}

void GUIContainer::render(SDL_Renderer *renderer, double parent_x,
                          double parent_y) {
  SDL_FRect dst = get_bounding_rect();
  if (!dst.w || !dst.h)
    return;
  dst.x += parent_x;
  dst.y += parent_y;

  if (skin != NULL) {
    if (cache_is_outdated)
      update_cache(renderer);
    SDL_RenderTexture(renderer, cache, NULL, &dst);
  }

  /* Mouse state debug */
  if (mouse_over) {
    if (mouse_down)
      SDL_SetRenderDrawColor(renderer, 0x22, 0x11, 0xFF, 0xFF);
    else
      SDL_SetRenderDrawColor(renderer, 0x33, 0xEE, 0xEE, 0xFF);
  } else
    SDL_SetRenderDrawColor(renderer, 0xEE, 0xEE, 0, 0xFF);
  SDL_RenderRect(renderer, &dst);

  for (GUIContainer *c : children)
    c->render(renderer, dst.x, dst.y);
}
