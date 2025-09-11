#ifndef GUI_SKIN_HPP_
#define GUI_SKIN_HPP_

#include <SDL3/SDL_rect.h>
#include <Texture.hpp>

class GUISkin {
private:
  Texture *texture;
  SDL_FRect top_right;
  SDL_FRect bottom_right;
  SDL_FRect bottom_left;
  SDL_FRect top_left;
  void render_top_right(SDL_FRect container);
  void render_top_left(SDL_FRect container);

public:
  GUISkin(Texture *texture, SDL_FRect top_right, SDL_FRect bottom_right,
          SDL_FRect bottom_left, SDL_FRect top_left);

  void render(SDL_FRect container);
};

#endif
