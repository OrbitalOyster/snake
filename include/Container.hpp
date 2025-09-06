#ifndef CONTAINER_HPP_
#define CONTAINER_HPP_

#include <SDL3/SDL_rect.h>
#include <vector>

class Container {
private:
  float x, y;
  float w, h;
  std::vector<Container *> children;

public:
  Container(float x, float y, float w, float h);
  SDL_FRect get_bounding_rect() const;
  void resize(float new_width, float new_height);
  void add_container(Container *container);
  void render();
};

#endif
