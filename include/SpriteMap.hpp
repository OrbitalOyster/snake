#ifndef SPRITE_MAP_HPP_
#define SPRITE_MAP_HPP_

#include <SDL3/SDL_render.h>
#include <string>

struct SpriteMapConfig {
  std::string key;
  unsigned x;
  unsigned y;
  unsigned w;
  unsigned h;
  unsigned n;
  unsigned fps;
};

class SpriteMap {
private:
  SDL_Renderer *renderer;

public:
  SpriteMap(const struct SpriteMapConfig config, SDL_Renderer *renderer);
};

#endif
