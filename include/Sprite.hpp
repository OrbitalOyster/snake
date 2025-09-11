#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>
#include <SpriteMap.hpp>
#include <Texture.hpp>

class Sprite {
private:
  float x, y;
  float w, h;
  const Texture *texture;
  const SpriteMap *sprite_map;
  unsigned long animation_start_time;

public:
  Sprite(float x, float y, float w, float h, Texture *texture);
  Sprite(float x, float y, float w, float h, Texture *texture,
         const SpriteMap *sprite_map);
  SDL_FRect get_bounding_rect() const;
  void render(unsigned long ticks) const;
};

#endif
