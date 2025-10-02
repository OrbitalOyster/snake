#ifndef SPRITE_MAP_HPP_
#define SPRITE_MAP_HPP_

#include <SDL3/SDL_render.h>
#include <string>

struct SpriteMapConfig {
  std::string key;
  std::string texture;
  unsigned x, y;
  unsigned w, h;
  unsigned n;
  unsigned fps;
};

class SpriteMap {
private:
  float x, y;
  float w, h;
  unsigned n;
  unsigned fps;

  unsigned long ticks_per_loop;
  unsigned long frame_size;

public:
  SpriteMap(float x, float y, float w, float h, unsigned n, unsigned fps);
  SpriteMap(const struct SpriteMapConfig config);
  SDL_FRect get_frame(unsigned long animation_start_time,
                      unsigned long ticks) const;
};

#endif
