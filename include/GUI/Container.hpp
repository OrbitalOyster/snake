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
  bool is_mouse_over = false;
  bool is_mouse_down = false;
  /* Cache, updating on resize */
  SDL_Texture *cache = NULL;
  bool cache_is_outdated = false;
  GUISkin *skin = NULL;
  GUISkin *default_skin = NULL;
  GUISkin *mouse_over_skin = NULL;
  GUISkin *mouse_down_skin = NULL;
  std::vector<GUIContainer *> children;
  std::vector<GUIText *> texts;
  GUIContainer *get_child(float x, float y);

public:
  GUIContainer();
  GUIContainer(GUILayout layout);
  void set_default_skin(GUISkin *skin);
  void set_mouse_over_skin(GUISkin *skin);
  void set_mouse_down_skin(GUISkin *skin);
  void set_min_width(GUIUnit min_width);
  void set_min_height(GUIUnit min_height);
  SDL_FRect get_bounding_rect() const;
  int get_width() const;
  int get_height() const;
  bool get_is_mouse_over() const;
  bool get_is_mouse_down() const;
  void update(int parent_width, int parent_height);
  void on_parent_resize(int new_parent_width, int new_parent_height);
  void add_container(GUIContainer *container);
  void add_text(GUIText *text);
  void update_cache(SDL_Renderer *renderer);
  void on_mouse_enter();
  void on_mouse_leave();
  void on_mouse_move(float x1, float y1, float x2, float y2);
  void on_mouse_down(float x, float y);
  void on_mouse_up(float x, float y);
  void render(SDL_Renderer *renderer, float parent_x, float parent_y);
};

#endif
