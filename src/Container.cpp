#include <Container.hpp>

Container::Container(float x, float y, float w, float h)
    : x(x), y(y), w(w), h(h) {}

SDL_FRect Container::get_bounding_rect() const { return {x, y, w, h}; }

void Container::on_parent_resize(float new_parent_width,
                                 float new_parent_height) {}

void Container::add_container(Container *container) {
  children.push_back(container);
}

void Container::resize(float new_width, float new_height) {
  w = new_width;
  h = new_height;
}
