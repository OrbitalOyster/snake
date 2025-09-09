#include <Container.hpp>

Container::Container() {}

void Container::set_sizing(GUISizing horizontal_sizing,
                           GUISizing vertical_sizing) {
  this->horizontal_sizing = horizontal_sizing;
  this->vertical_sizing = vertical_sizing;
}

SDL_FRect Container::get_bounding_rect() const { return {x, y, w, h}; }

float Container::get_width() const { return w; }

float Container::get_height() const { return h; }

void Container::update(float parent_width, float parent_height) {
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

void Container::render(SDL_Renderer *renderer) {
  const SDL_FRect dst = get_bounding_rect();
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0, 0xFF);
  SDL_RenderRect(renderer, &dst);

  for (Container *c : children) {
    c->render(renderer);
  }
}
