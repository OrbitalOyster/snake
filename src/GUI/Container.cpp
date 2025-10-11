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

void GUIContainer::set_default_skin(GUISkin *skin) {
  this->default_skin = skin;
  this->skin = this->default_skin;
  cache_is_outdated = true;
}

void GUIContainer::set_mouse_over_skin(GUISkin *skin) {
  this->mouse_over_skin = skin;
  cache_is_outdated = true;
}

void GUIContainer::set_mouse_down_skin(GUISkin *skin) {
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
  // SDL_Log("Mouse enter %f %f %f %f", rect.x, rect.y, rect.w, rect.h);
}
void GUIContainer::on_mouse_leave() {
  is_mouse_over = false;
  if (mouse_over_skin) {
    skin = default_skin;
    cache_is_outdated = true;
  }
  // SDL_Log("Mouse leave %f %f %f %f", rect.x, rect.y, rect.w, rect.h);
}

void GUIContainer::on_mouse_down(float x, float y) {
  SDL_Log("Mouse down %f %f %f %f", rect.x, rect.y, rect.w, rect.h);
  for (GUIContainer *child : children) {
    const SDL_FRect rect = child->get_bounding_rect();
    if (x > rect.x && x < rect.x + rect.w && y > rect.y &&
        y < rect.y + rect.h) {
      child->on_mouse_down(x, y);
      is_mouse_down = true;
      return;
    } else if (child->get_is_mouse_down())
      child->on_mouse_up(x, y);
  }
  is_mouse_down = true;
  if (mouse_down_skin) {
    skin = mouse_down_skin;
    cache_is_outdated = true;
  }
}

void GUIContainer::on_mouse_up(float x, float y) {
  SDL_Log("Mouse up %f %f %f %f", rect.x, rect.y, rect.w, rect.h);
  is_mouse_down = false;
  if (mouse_down_skin) {
    skin = default_skin;
    cache_is_outdated = true;
  }
}

void GUIContainer::on_mouse_over(float x, float y) {
  for (GUIContainer *child : children) {
    const SDL_FRect rect = child->get_bounding_rect();
    if (x > rect.x && x < rect.x + rect.w && y > rect.y &&
        y < rect.y + rect.h) {
      child->on_mouse_over(x, y);
      if (is_mouse_over)
        on_mouse_leave();
      return;
    } else if (child->get_is_mouse_over())
      child->on_mouse_leave();
  }
  if (!is_mouse_over)
    on_mouse_enter();
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
