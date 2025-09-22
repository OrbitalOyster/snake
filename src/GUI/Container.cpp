#include <GUI/Container.hpp>

GUIContainer::GUIContainer() {}

GUIContainer::GUIContainer(GUISizing horizontal_sizing,
                           GUISizing vertical_sizing)
    : horizontal_sizing(horizontal_sizing), vertical_sizing(vertical_sizing) {}

void GUIContainer::set_skin(GUISkin *skin) {
  this->skin = skin;
  cache_is_outdated = true;
}

void GUIContainer::set_min_width(GUIUnit min_width) {
  this->min_width = min_width;
}

void GUIContainer::set_min_height(GUIUnit min_height) {
  this->min_height = min_height;
}

SDL_FRect GUIContainer::get_bounding_rect() const {
  return {(float)x, (float)y, (float)w, (float)h};
}
int GUIContainer::get_width() const { return w; }
int GUIContainer::get_height() const { return h; }

void GUIContainer::update(int parent_width, int parent_height) {
  int old_w = w, old_h = h;
  horizontal_sizing.calculate(parent_width, &x, &w);
  vertical_sizing.calculate(parent_height, &y, &h);
  int min_width_p = min_width.to_pixels(parent_width);
  int min_height_p = min_height.to_pixels(parent_height);
  if (w < min_width_p)
    w = min_width_p;
  if (h < min_height_p)
    h = min_height_p;
  if (w != old_w || h != old_h)
    cache_is_outdated = true;
  for (GUIContainer *c : children)
    c->update(w, h);
}

void GUIContainer::add_container(GUIContainer *container) {
  children.push_back(container);
  children.back()->update(w, h);
}

void GUIContainer::update_cache(SDL_Renderer *renderer) {
  if (cache != NULL)
    SDL_DestroyTexture(cache);
  cache = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
                            SDL_TEXTUREACCESS_TARGET, w, h);
  SDL_SetRenderTarget(renderer, cache);
  skin->render({0, 0, (float)w, (float)h});
  SDL_SetRenderTarget(renderer, NULL);
  cache_is_outdated = false;
}

void GUIContainer::render(SDL_Renderer *renderer, int parent_x, int parent_y) {
  SDL_FRect dst = get_bounding_rect();
  if (!dst.w || !dst.h)
    return;
  dst.x += parent_x;
  dst.y += parent_y;
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0, 0xFF);
  SDL_RenderRect(renderer, &dst);
  if (skin != NULL) {
    if (cache_is_outdated)
      update_cache(renderer);
    SDL_RenderTexture(renderer, cache, NULL, &dst);
  }
  for (GUIContainer *c : children)
    c->render(renderer, dst.x, dst.y);
}
