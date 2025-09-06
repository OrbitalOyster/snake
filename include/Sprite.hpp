#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <SDL3_image/SDL_image.h>
#include <SpriteMap.hpp>

class Sprite {
private:
  float x, y;
  float w, h;
  const SpriteMap *sprite_map;
  unsigned long animation_start;

public:
  Sprite(float x, float y, float w, float h, const SpriteMap *sprite_map);
  SDL_FRect get_bounding_rect();
  void set_animation();
  void render();
};

#endif
