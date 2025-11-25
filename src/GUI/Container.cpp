#include <GUI/Container.hpp>
#include <SDL3/SDL_log.h>
#include <cmath>
#include <vector>

GUIContainer::GUIContainer() {}

GUIContainer::GUIContainer(GUILayout layout) : layout(layout) {}

void GUIContainer::update(float parent_width, float parent_height) {
  int old_w = rect.w, old_h = rect.h;
  rect = layout.calculate(parent_width, parent_height);

  /* Adjust min. size */
  if (rect.w < min_width.to_pixels(parent_width))
    rect.w = min_width.to_pixels(parent_width);
  if (rect.h < min_height.to_pixels(parent_height))
    rect.h = min_height.to_pixels(parent_height);

  if (rect.w != old_w || rect.h != old_h)
    cache_is_outdated = true;

  for (GUIContainer *c : children)
    c->update(rect.w, rect.h);

  /* Re-check mouse position */
  reset_focus();
  reset_mouse();
}

void GUIContainer::set_skin(Skin *new_skin) {
  this->the_skin = new_skin;
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

float GUIContainer::get_width() const { return rect.w; }
float GUIContainer::get_height() const { return rect.h; }
bool GUIContainer::get_is_mouse_over() const { return is_mouse_over; };
bool GUIContainer::get_is_mouse_down() const { return is_mouse_down; };

void GUIContainer::add_container(GUIContainer *container) {
  children.push_back(container);
  children.back()->update(rect.w, rect.h);
}

void GUIContainer::add_text(GUIText *text) { texts.push_back(text); }

void GUIContainer::update_cache(SDL_Renderer *renderer) {
  if (cache != NULL)
    SDL_DestroyTexture(cache);
  cache = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
                            SDL_TEXTUREACCESS_TARGET, rect.w, rect.h);
  SDL_SetRenderTarget(renderer, cache);

  if (is_mouse_down)
    the_skin->render({0, 0, rect.w, rect.h}, Active);
  else if (is_mouse_over)
    the_skin->render({0, 0, rect.w, rect.h}, Hover);
  else
    the_skin->render({0, 0, rect.w, rect.h}, Base);

  for (GUIText *t : texts)
    t->render(renderer, rect.w, rect.h);
  SDL_SetRenderTarget(renderer, NULL);
  cache_is_outdated = false;
}

std::vector<GUIContainer *> GUIContainer::get_children(float x, float y) {
  std::vector<GUIContainer *> result;
  for (GUIContainer *child : children) {
    const SDL_FRect rect = child->get_bounding_rect();
    if (x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h)
      result.push_back(child);
    // return child;
  }
  // return NULL;
  return result;
}

void GUIContainer::on_mouse_enter() {
  is_mouse_over = true;
  cache_is_outdated = true;
  if (cursor)
    SDL_SetCursor(cursor);
  // SDL_Log("Mouse enter %f %f %f %f", rect.x, rect.y, rect.w, rect.h);
}

void GUIContainer::on_mouse_leave() {
  is_mouse_over = false;
  is_mouse_down = false;
  cache_is_outdated = true;
  if (cursor)
    SDL_SetCursor(SDL_GetDefaultCursor());
  for (GUIContainer *child : children)
    child->on_mouse_leave();
  // SDL_Log("Mouse leave %f %f %f %f", rect.x, rect.y, rect.w, rect.h);
}

bool GUIContainer::on_mouse_down(float x, float y) {
  // SDL_Log("Mouse down %f %f %f %f %b", rect.x, rect.y, rect.w, rect.h,
  // is_draggable);
  std::vector<GUIContainer *> child = get_children(x, y);
  if (!child.empty())
    return child.back()->on_mouse_down(x, y);
  else {
    is_mouse_down = true;
    cache_is_outdated = true;
    return is_bubbling;
  }
}

void GUIContainer::on_mouse_up(float x, float y) {
  // SDL_Log("Mouse up %f %f %f %f", rect.x, rect.y, rect.w, rect.h);
  std::vector<GUIContainer *> child = get_children(x, y);
  if (!child.empty())
    child.back()->on_mouse_up(x, y);
  else {
    if (is_mouse_down) {
      is_mouse_down = false;
      //       SDL_Log("Mouse click");
    }
    cache_is_outdated = true;
  }
}

void GUIContainer::on_mouse_move(float x1, float y1, float x2, float y2) {
  // SDL_Log("Mouse move %f %f %f %f", rect.x, rect.y, rect.w, rect.h);
  // SDL_Log("%f %f %f %f", x1, y1, x2, y2);
  std::vector<GUIContainer *> child1 = get_children(x1, y1);
  std::vector<GUIContainer *> child2 = get_children(x2, y2);

  /* Left child1 */
  if (!child1.empty() && (child2.empty() || child1.back() != child2.back()))
    child1.back()->on_mouse_leave();
  /* Entered child2 */
  if (!child2.empty())
    child2.back()->on_mouse_move(x1, y1, x2, y2);
  else if (!is_mouse_over)
    on_mouse_enter();
}

void GUIContainer::on_mouse_drag(float x, float y, float dx, float dy) {
  if (is_draggable) {
    // SDL_Log("Container drag %f %f %f %f %b", x, y, dx, dy, is_draggable);
    // this->rect.x += dx;
    // this->rect.y += dy;
    layout.move(dx, dy);
    // rect.x = layout.get_left();
    // SDL_Log("%f %f", this->rect.x, this->rect.y);
    update(get_width(), get_height());
  }

  for (GUIContainer *child : children)
    if (child->get_is_mouse_over())
      child->on_mouse_drag(x, y, dx, dy);
}

void GUIContainer::reset_focus() {
  on_mouse_leave();
  for (GUIContainer *child : children)
    child->reset_focus();
}

void GUIContainer::reset_mouse() {
  float x = 0, y = 0;
  SDL_GetMouseState(&x, &y);
  on_mouse_move(x, y, x, y);
}

void GUIContainer::render(SDL_Renderer *renderer, float parent_x,
                          float parent_y) {
  SDL_FRect dst = get_bounding_rect();
  dst.x = round(dst.x);
  dst.y = round(dst.y);
  dst.w = round(dst.w);
  dst.h = round(dst.h);
  if (!dst.w || !dst.h)
    return;
  dst.x += parent_x;
  dst.y += parent_y;
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0, 0xFF);
  // SDL_RenderRect(renderer, &dst);
  if (the_skin != NULL) {
    if (cache_is_outdated)
      update_cache(renderer);
    SDL_RenderTexture(renderer, cache, NULL, &dst);
  }

  for (GUIContainer *c : children)
    c->render(renderer, dst.x, dst.y);
}
