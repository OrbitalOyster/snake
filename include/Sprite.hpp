#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>
#include <SpriteMap.hpp>
#include <Texture.hpp>

class Sprite {
private:
  double x, y;
  double w, h;
  const Texture *texture;
  const SpriteMap *sprite_map;
  unsigned long animation_start_time;

public:
  Sprite(double x, double y, double w, double h, Texture *texture, const SpriteMap *sprite_map = NULL);
  SDL_FRect get_bounding_rect() const;
  void render() const;
  void render(unsigned long ticks) const;
};

#endif
