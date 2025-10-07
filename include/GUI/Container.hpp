#ifndef GUI_CONTAINER_HPP_
#define GUI_CONTAINER_HPP_

#include <GUI/Layout.hpp>
#include <GUI/Segment.hpp>
#include <GUI/Skin.hpp>
#include <GUI/Text.hpp>
#include <GUI/Unit.hpp>
#include <vector>

class GUIContainer {
private:
  /* Layout */
  GUILayout layout;
  /* Actual dimensions */
  SDL_FRect rect;
  GUIUnit min_width, min_height;
  /* Cache, updating on resize */
  SDL_Texture *cache = NULL;
  bool cache_is_outdated = false;
  GUISkin *skin = NULL;
  std::vector<GUIContainer *> children;
  std::vector<GUIText *> texts;

public:
  GUIContainer();
  GUIContainer(GUILayout layout);
  void set_skin(GUISkin *skin);
  void set_min_width(GUIUnit min_width);
  void set_min_height(GUIUnit min_height);
  SDL_FRect get_bounding_rect() const;
  int get_width() const;
  int get_height() const;
  void update(int parent_width, int parent_height);
  void on_parent_resize(int new_parent_width, int new_parent_height);
  void add_container(GUIContainer *container);
  void add_text(GUIText *text);
  void update_cache(SDL_Renderer *renderer);
  bool on_mouse_over(float x, float y);
  bool on_mouse_down(float x, float y);
  void render(SDL_Renderer *renderer, float parent_x, float parent_y);
};

#endif
