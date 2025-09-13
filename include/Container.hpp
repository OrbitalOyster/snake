#ifndef CONTAINER_HPP_
#define CONTAINER_HPP_

#include <GUISizing.hpp>
#include <GUISkin.hpp>
#include <GUIUnit.hpp>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <vector>

class Container {
private:
  /* Alignment chicanery */
  GUISizing horizontal_sizing, vertical_sizing;
  /* Actual dimensions */
  int x, y;
  int w, h;
  GUISkin *skin = NULL;
  std::vector<Container *> children;

public:
  Container();
  Container(GUISizing horizontal_sizing, GUISizing vertical_sizing);
  void set_skin(GUISkin *skin);
  SDL_FRect get_bounding_rect() const;
  int get_width() const;
  int get_height() const;
  void update(int parent_width, int parent_height);
  void resize(int new_width, int new_height);
  void on_parent_resize(int new_parent_width, int new_parent_height);
  void add_container(Container *container);
  void render(SDL_Renderer *renderer, int parent_x, int parent_y);
};

#endif
