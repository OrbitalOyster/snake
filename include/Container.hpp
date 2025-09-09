#ifndef CONTAINER_HPP_
#define CONTAINER_HPP_

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <vector>

class Container {
private:
  float x, y;
  float w, h;

  float top, right, bottom, left;

  std::vector<Container *> children;

public:
  Container(float x, float y, float w, float h);
  SDL_FRect get_bounding_rect() const;
  void update(float parent_width, float parent_height);
  void resize(float new_width, float new_height);
  void on_parent_resize(float new_parent_width, float new_parent_height);
  void add_container(Container *container);
  void render(SDL_Renderer *renderer);
};

#endif
