#include <Container.hpp>

Container::Container(float x, float y, float w, float h)
    : x(x), y(y), w(w), h(h) {}

SDL_FRect Container::get_bounding_rect() const { return {x, y, w, h}; }

void Container::update(float parent_width, float parent_height) {

}

void Container::on_parent_resize(float new_parent_width,
                                 float new_parent_height) {}

void Container::add_container(Container *container) {
  children.push_back(container);
  children.back()->update(w, h);
}

void Container::resize(float new_width, float new_height) {
  w = new_width;
  h = new_height;
}

void Container::render(SDL_Renderer *renderer) {
  const SDL_FRect dst = get_bounding_rect();
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0, 0xFF);
  SDL_RenderRect(renderer, &dst);

  for (Container *c : children) {
    c->render(renderer);
  }
}
