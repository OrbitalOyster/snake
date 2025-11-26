#ifndef SPRITE_MAP_HPP_
#define SPRITE_MAP_HPP_

#include <SDL3/SDL_render.h>

class SpriteMap {
private:
  double x, y;
  double w, h;
  unsigned n;
  unsigned fps;
  unsigned long ticks_per_loop;
  unsigned long frame_size;

public:
  SpriteMap(double x, double y, double w, double h, unsigned n, unsigned fps);
  SDL_FRect get_frame(unsigned long animation_start_time,
                      unsigned long ticks) const;
};

#endif
