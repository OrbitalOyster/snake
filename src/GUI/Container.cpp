#include "SDL3/SDL_log.h"
#include "SDL3/SDL_rect.h"
#include <GUI/Container.hpp>
#include <Utils.hpp>
#include <cmath>

bool point_within_rect(double x, double y, SDL_FRect rect) {
  return x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h;
}

GUIContainer::GUIContainer(std::string tag) : tag(tag) {}

GUIContainer::GUIContainer(std::string tag, GUILayout layout)
    : tag(tag), layout(layout) {}

std::string GUIContainer::get_tag() const { return tag; }

std::vector<GUIContainer *> GUIContainer::get_all_children() {
  std::vector<GUIContainer *> result = children;
  if (result.empty())
    return result;
  for (GUIContainer *child : children) {
    std::vector<GUIContainer *> tmp = child->get_all_children();
    result.insert(result.end(), tmp.begin(), tmp.end());
  }
  return result;
}

bool GUIContainer::is_draggable() { return draggable; }

void GUIContainer::on_resize(double parent_x, double parent_y,
                             double parent_width, double parent_height) {
  double old_w = rect.w, old_h = rect.h;
  rect = layout.calculate(parent_x, parent_y, parent_width, parent_height);

  /* Adjust min. size */
  if (rect.w < min_width.to_pixels(parent_width))
    rect.w = min_width.to_pixels(parent_width);
  if (rect.h < min_height.to_pixels(parent_height))
    rect.h = min_height.to_pixels(parent_height);

  if (rect.w != old_w || rect.h != old_h)
    cache_is_outdated = true;

  for (GUIContainer *child : children)
    child->on_resize(rect.x, rect.y, rect.w, rect.h);
}

void GUIContainer::set_skin(Skin *new_skin) {
  skin = new_skin;
  cache_is_outdated = true;
}

void GUIContainer::set_cursor(SDL_Cursor *new_cursor) { cursor = new_cursor; }

void GUIContainer::set_min_width(GUIUnit new_min_width) {
  min_width = new_min_width;
}

void GUIContainer::set_min_height(GUIUnit new_min_height) {
  min_height = new_min_height;
}

void GUIContainer::set_draggable(bool new_draggable) {
  draggable = new_draggable;
}

SDL_FRect GUIContainer::get_bounding_rect() const { return rect; }

void GUIContainer::move(double dx, double dy) {
  rect.x += dx;
  rect.y += dy;
}

double GUIContainer::get_width() const { return rect.w; }
double GUIContainer::get_height() const { return rect.h; }
bool GUIContainer::is_mouse_over() const { return mouse_over; };
bool GUIContainer::is_mouse_down() const { return mouse_down; };

void GUIContainer::add_container(GUIContainer *container) {
  children.push_back(container);
  children.back()->on_resize(rect.x, rect.y, rect.w, rect.h);
}

void GUIContainer::add_text(GUIText *text) { texts.push_back(text); }

void GUIContainer::add_sprite(Sprite *sprite) { sprites.push_back(sprite); };

void GUIContainer::update_cache(SDL_Renderer *renderer) {
  if (cache != NULL)
    SDL_DestroyTexture(cache);
  cache =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
                        SDL_TEXTUREACCESS_TARGET, round(rect.w), round(rect.h));
  SDL_SetRenderTarget(renderer, cache);
  SDL_FRect dst = {0.0, 0.0, rect.w, rect.h};
  if (mouse_down)
    skin->render(&dst, Active);
  else if (mouse_over)
    skin->render(&dst, Hover);
  else
    skin->render(&dst, Base);
  for (GUIText *text : texts)
    text->render(renderer, rect.w, rect.h);
  for (Sprite *sprite : sprites)
    sprite->render();
  SDL_SetRenderTarget(renderer, NULL);
  cache_is_outdated = false;
}

GUIContainer *GUIContainer::find_child(double x, double y) {
  for (auto it = children.rbegin(); it != children.rend(); ++it) {
    GUIContainer *child = (*it);
    if (point_within_rect(x, y, child->get_bounding_rect()))
      return child->find_child(x, y);
  }
  return this;
}

void GUIContainer::on_mouse_enter() {
  SDL_Log("Mouse enter %s", tag.c_str());
  mouse_over = true;
  cache_is_outdated = true;
  if (cursor)
    SDL_SetCursor(cursor);
}

void GUIContainer::on_mouse_leave() {
  for (GUIContainer *child : children)
    child->on_mouse_leave();
  if (!mouse_over)
    return;
  SDL_Log("Mouse leave %s", tag.c_str());
  if (cursor)
    SDL_SetCursor(SDL_GetDefaultCursor());
  mouse_over = false;
  cache_is_outdated = true;
}

void GUIContainer::on_mouse_down() {
  SDL_Log("Mouse down %s", tag.c_str());
  mouse_down = true;
  cache_is_outdated = true;
}

void GUIContainer::reset_mouse_down() {
  mouse_down = false;
  cache_is_outdated = true;
}

void GUIContainer::on_mouse_up() {
  SDL_Log("Mouse up %s", tag.c_str());
  if (mouse_over && mouse_down)
    on_mouse_click();
  reset_mouse_down();
}

void GUIContainer::on_mouse_click() { SDL_Log("Mouse click %s", tag.c_str()); }

void GUIContainer::render(SDL_Renderer *renderer) {
  SDL_FRect dst = get_bounding_rect();
  if (!dst.w || !dst.h)
    return;
  if (skin != NULL) {
    if (cache_is_outdated)
      update_cache(renderer);
    SDL_RenderTexture(renderer, cache, NULL, &dst);
  }

  /* Mouse state debug */
  /*
  if (mouse_over) {
    if (mouse_down)
      SDL_SetRenderDrawColor(renderer, 0x22, 0x11, 0xFF, 0xFF);
    else
      SDL_SetRenderDrawColor(renderer, 0x33, 0xEE, 0xEE, 0xFF);
  } else
    SDL_SetRenderDrawColor(renderer, 0xEE, 0xEE, 0, 0xFF);
  SDL_RenderRect(renderer, &dst);
  */

  for (GUIContainer *c : children)
    c->render(renderer);
}
