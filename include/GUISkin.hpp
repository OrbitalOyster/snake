#ifndef GUI_SKIN_HPP_
#define GUI_SKIN_HPP_

#include "SDL3/SDL_render.h"
#include <SDL3/SDL_rect.h>

class GUISkin {
private:
  SDL_Texture *texture;
  SDL_FRect top_right;
  SDL_FRect bottom_right;
  SDL_FRect bottom_left;
  SDL_FRect top_left;

public:
  GUISkin(SDL_Texture *texture, SDL_FRect top_right, SDL_FRect bottom_right,
          SDL_FRect bottom_left, SDL_FRect top_left);
};

#endif
