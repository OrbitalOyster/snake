#ifndef CONTAINER_HPP_
#define CONTAINER_HPP_

#include <GUIUnit.hpp>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <vector>

class Container {
private:
  /* Actual dimensions */
  float x, y;
  float w, h;

  GUIUnit u_left, u_width, u_right;
  GUIUnit u_top, u_height, u_bottom;

  std::vector<Container *> children;

public:
  Container();
  void set_horizontal_sizing(GUIUnit left, GUIUnit width, GUIUnit right);
  void set_vertical_sizing(GUIUnit top, GUIUnit height, GUIUnit bottom);
  SDL_FRect get_bounding_rect() const;
  float get_width() const;
  float get_height() const;
  void update(float parent_width, float parent_height);
  void resize(float new_width, float new_height);
  void on_parent_resize(float new_parent_width, float new_parent_height);
  void add_container(Container *container);
  void render(SDL_Renderer *renderer);
};

#endif
