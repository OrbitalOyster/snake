#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <SDL3_image/SDL_image.h>

class Sprite {
private:
  SDL_Texture *texture;
  float x, y;
  float width, height;

public:
  Sprite();
  SDL_FRect get_bounding_rect();
};

#endif
