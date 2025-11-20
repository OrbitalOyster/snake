#include <GUI/Container.hpp>
#include <SDL3/SDL_log.h>

GUIContainer::GUIContainer() {}

GUIContainer::GUIContainer(GUILayout layout) : layout(layout) {}

void GUIContainer::update(int parent_width, int parent_height) {
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

void GUIContainer::set_default_skin(Stretchable *skin) {
  this->default_skin = skin;
  this->skin = this->default_skin;
  cache_is_outdated = true;
}

void GUIContainer::set_mouse_over_skin(Stretchable *skin) {
  this->mouse_over_skin = skin;
  cache_is_outdated = true;
}

void GUIContainer::set_cursor(SDL_Cursor *cursor) { this->cursor = cursor; }

void GUIContainer::set_mouse_down_skin(Stretchable *skin) {
  this->mouse_down_skin = skin;
  cache_is_outdated = true;
}

void GUIContainer::set_min_width(GUIUnit min_width) {
  this->min_width = min_width;
}

void GUIContainer::set_min_height(GUIUnit min_height) {
  this->min_height = min_height;
}

SDL_FRect GUIContainer::get_bounding_rect() const { return rect; }

int GUIContainer::get_width() const { return rect.w; }
int GUIContainer::get_height() const { return rect.h; }
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
  skin->render({0, 0, rect.w, rect.h});
  for (GUIText *t : texts)
    t->render(renderer, rect.w, rect.h);
  SDL_SetRenderTarget(renderer, NULL);
  cache_is_outdated = false;
}

GUIContainer *GUIContainer::get_child(float x, float y) {
  for (GUIContainer *child : children) {
    const SDL_FRect rect = child->get_bounding_rect();
    if (x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h)
      return child;
  }
  return NULL;
}

void GUIContainer::on_mouse_enter() {
  is_mouse_over = true;
  if (mouse_over_skin) {
    skin = mouse_over_skin;
    cache_is_outdated = true;
  }
  if (cursor)
    SDL_SetCursor(cursor);
  // SDL_Log("Mouse enter %f %f %f %f", rect.x, rect.y, rect.w, rect.h);
}

void GUIContainer::on_mouse_leave() {
  is_mouse_over = false;
  if (mouse_over_skin) {
    skin = default_skin;
    cache_is_outdated = true;
  }
  if (cursor)
    SDL_SetCursor(SDL_GetDefaultCursor());
  // SDL_Log("Mouse leave %f %f %f %f", rect.x, rect.y, rect.w, rect.h);
}

void GUIContainer::on_mouse_down(float x, float y) {
  // SDL_Log("Mouse down %f %f %f %f", rect.x, rect.y, rect.w, rect.h);
  GUIContainer *child = get_child(x, y);
  if (child)
    child->on_mouse_down(x, y);
  else {
    is_mouse_down = true;
    if (mouse_down_skin) {
      skin = mouse_down_skin;
      cache_is_outdated = true;
    }
  }
}

void GUIContainer::on_mouse_up(float x, float y) {
  // SDL_Log("Mouse up %f %f %f %f", rect.x, rect.y, rect.w, rect.h);
  GUIContainer *child = get_child(x, y);
  if (child)
    child->on_mouse_up(x, y);
  else {
    is_mouse_down = false;
    if (mouse_down_skin) {
      skin = mouse_over_skin;
      cache_is_outdated = true;
    }
  }
}

void GUIContainer::on_mouse_move(float x1, float y1, float x2, float y2) {
  // SDL_Log("Mouse move %f %f %f %f", rect.x, rect.y, rect.w, rect.h);
  // SDL_Log("%f %f %f %f", x1, y1, x2, y2);
  GUIContainer *child1 = get_child(x1, y1);
  GUIContainer *child2 = get_child(x2, y2);
  /* Left child1 */
  if (child1 && child1 != child2)
    child1->on_mouse_leave();
  /* Entered child2 */
  if (child2)
    child2->on_mouse_move(x1, y1, x2, y2);
  else if (!is_mouse_over)
    on_mouse_enter();
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
  if (!dst.w || !dst.h)
    return;
  dst.x += parent_x;
  dst.y += parent_y;
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0, 0xFF);
  // SDL_RenderRect(renderer, &dst);
  if (skin != NULL) {
    if (cache_is_outdated)
      update_cache(renderer);
    SDL_RenderTexture(renderer, cache, NULL, &dst);
  }

  for (GUIContainer *c : children)
    c->render(renderer, dst.x, dst.y);
}
