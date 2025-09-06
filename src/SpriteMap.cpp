#include "SDL3/SDL_render.h"
#include <SpriteMap.hpp>

#include <iostream>
#include <stdexcept>

SpriteMap::SpriteMap(const struct SpriteMapConfig config, SDL_Texture * texture) : texture(texture) {
  x = (float)config.x;
  y = (float)config.y;
  w = (float)config.w;
  h = (float)config.h;
  n = config.n;
  fps = config.fps;

  if (1000 % fps)
    throw std::runtime_error("Bad fps value (" + std::to_string(fps) +
                             ") for SpriteMap " + config.key);

  frame_size = 1000 / fps;
}

SDL_Texture * SpriteMap::get_texture() const {
    return texture;
}

SDL_FRect SpriteMap::get_frame(unsigned long animation_start_time,
                               unsigned long ticks) const {
  const unsigned long time_passed = ticks - animation_start_time;
  const unsigned int frames_passed = time_passed / frame_size;
  const unsigned current_frame = frames_passed % n;
  return {x + current_frame * w, y, w, h};
}
