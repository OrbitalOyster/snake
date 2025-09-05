#ifndef SPRITE_MAP_HPP_
#define SPRITE_MAP_HPP_

#include <SDL3/SDL_render.h>
#include <string>

struct SpriteMapConfig {
  std::string key;
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

public:
  SpriteMap(const struct SpriteMapConfig config);
};

#endif
