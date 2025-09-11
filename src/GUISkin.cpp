#include <GUISkin.hpp>

GUISkin::GUISkin(Texture *texture, SDL_FRect top_right, SDL_FRect bottom_right,
                 SDL_FRect bottom_left, SDL_FRect top_left)
    : texture(texture), top_right(top_right), bottom_right(bottom_right),
      bottom_left(bottom_left), top_left(top_left) {}

void GUISkin::render_top_right(SDL_FRect container) {
  SDL_FRect dst = {container.x + container.w - top_right.w, container.y,
                   top_right.w, top_right.h};
  texture->render(&top_right, &dst);
}

void GUISkin::render_top_left(SDL_FRect container) {
  SDL_FRect dst = {container.x, container.y, top_left.w, top_left.h};
  texture->render(&top_left, &dst);
}

void GUISkin::render(SDL_FRect container) {
  render_top_right(container);
  render_top_left(container);
}
