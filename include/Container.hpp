#ifndef CONTAINER_HPP_
#define CONTAINER_HPP_

#include <SDL3/SDL_rect.h>

class Container {
private:
  float x, y;
  float w, h;

public:
  Container(float x, float y, float w, float h);
  SDL_FRect get_bounding_rect() const;
  void render();
};

#endif
