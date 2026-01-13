#ifndef SPRITE_MAP_HPP_
#define SPRITE_MAP_HPP_

#include <SDL3/SDL_render.h>

class SpriteMap {
private:
  int x, y;
  int w, h;
  unsigned n;
  unsigned fps;
  unsigned long ticks_per_frame;

public:
  SpriteMap(int x, int y, unsigned w, unsigned h, unsigned n = 1,
            unsigned fps = 1);
  SDL_FRect get_frame(unsigned long animation_start_time,
                      unsigned long ticks) const;
};

#endif
