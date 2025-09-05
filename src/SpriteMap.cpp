#include <SpriteMap.hpp>

#include <iostream>

SpriteMap::SpriteMap(const struct SpriteMapConfig config) {
  x = (float)config.x;
  y = (float)config.y;
  w = (float)config.w;
  h = (float)config.h;
  n = config.n;
  fps = config.fps;

  std::cout << "Loaded" << std::endl;
}
