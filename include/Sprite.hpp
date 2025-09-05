#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <SDL3_image/SDL_image.h>
#include <SpriteMap.hpp>

class Sprite {
private:
  SpriteMap *sprite_map;
  float x, y;
  float w, h;
  unsigned long animation_start;

public:
  Sprite(SpriteMap *sprite_map, float x, float y, float w, float h);
  SDL_FRect get_bounding_rect();
  void set_animation();
  void render();
};

#endif
