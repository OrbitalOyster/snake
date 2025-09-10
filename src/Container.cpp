#include "GUISkin.hpp"
#include <Container.hpp>

Container::Container() {}

Container::Container(GUISizing horizontal_sizing, GUISizing vertical_sizing)
    : horizontal_sizing(horizontal_sizing), vertical_sizing(vertical_sizing) {}

void Container::set_skin(GUISkin *skin) { this->skin = skin; }

SDL_FRect Container::get_bounding_rect() const {
  return {(float)x, (float)y, (float)w, (float)h};
}
int Container::get_width() const { return w; }
int Container::get_height() const { return h; }

void Container::update(int parent_width, int parent_height) {
  horizontal_sizing.calculate(parent_width, &x, &w);
  vertical_sizing.calculate(parent_height, &y, &h);
  for (Container *c : children) {
    c->update(w, h);
  }
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

  for (Container *c : children) {
    c->render(renderer, dst.x, dst.y);
  }
}
