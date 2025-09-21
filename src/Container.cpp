#include "GUIUnit.hpp"
#include <Container.hpp>

Container::Container() {}

Container::Container(GUISizing horizontal_sizing, GUISizing vertical_sizing)
    : horizontal_sizing(horizontal_sizing), vertical_sizing(vertical_sizing) {}

void Container::set_skin(GUISkin *skin) { this->skin = skin; }

void Container::set_min_width(GUIUnit min_width) {
  this->min_width = min_width;
}

void Container::set_min_height(GUIUnit min_height) {
  this->min_height = min_height;
}

SDL_FRect Container::get_bounding_rect() const {
  return {(float)x, (float)y, (float)w, (float)h};
}
int Container::get_width() const { return w; }
int Container::get_height() const { return h; }

void Container::update(int parent_width, int parent_height) {
  int min_width_p = min_width.to_pixels(parent_width);
  int min_height_p = min_height.to_pixels(parent_height);
  horizontal_sizing.calculate(parent_width, &x, &w);
  vertical_sizing.calculate(parent_height, &y, &h);
  if (w < min_width_p)
    w = min_width_p;
  if (h < min_height_p)
    h = min_height_p;
  for (Container *c : children)
    c->update(w, h);
}

void Container::add_container(Container *container) {
  children.push_back(container);
  children.back()->update(w, h);
}

void Container::render(SDL_Renderer *renderer, int parent_x, int parent_y) {
  SDL_FRect dst = get_bounding_rect();
  dst.x += parent_x;
  dst.y += parent_y;
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0, 0xFF);
  SDL_RenderRect(renderer, &dst);

  if (skin != NULL)
    skin->render(dst);

  for (Container *c : children)
    c->render(renderer, dst.x, dst.y);
}
