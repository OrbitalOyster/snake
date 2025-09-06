#include <Container.hpp>

Container::Container(float x, float y, float w, float h)
    : x(x), y(y), w(w), h(h) {}

SDL_FRect Container::get_bounding_rect() const { return {x, y, w, h}; }
