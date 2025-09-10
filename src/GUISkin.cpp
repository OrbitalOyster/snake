#include <GUISkin.hpp>

GUISkin::GUISkin(SDL_Texture *texture, SDL_FRect top_right,
                 SDL_FRect bottom_right, SDL_FRect bottom_left,
                 SDL_FRect top_left)
    : texture(texture), top_right(top_right),
      bottom_right(bottom_right), bottom_left(bottom_left), top_left(top_left) {

}
