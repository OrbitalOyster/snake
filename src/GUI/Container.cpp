#include <GUI/Container.hpp>

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
}

void GUIContainer::set_skin(GUISkin *skin) {
  this->skin = skin;
  cache_is_outdated = true;
}

void GUIContainer::set_mouse_over_skin(GUISkin *skin) {
  this->mouse_over_skin = skin;
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

bool GUIContainer::on_mouse_over(float x, float y) {
  for (GUIContainer *child : children) {
    const SDL_FRect rect = child->get_bounding_rect();
    if (x > rect.x && x < rect.x + rect.w && y > rect.y &&
        y < rect.y + rect.h) {
      child->on_mouse_over(x, y);
      return false;
    }
  }
  // SDL_Log("%f %f", rect.x, rect.y);
  return true;
}

bool GUIContainer::on_mouse_down(float x, float y) {}

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
