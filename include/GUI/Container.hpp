#ifndef GUI_CONTAINER_HPP_
#define GUI_CONTAINER_HPP_

#include <GUI/Layout.hpp>
#include <GUI/Segment.hpp>
#include <GUI/Skin.hpp>
#include <GUI/Text.hpp>
#include <GUI/Unit.hpp>
#include <Stretchable.hpp>
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
  bool is_draggable = false;
  bool is_bubbling = true;
  /* Cache, updating on resize */
  SDL_Texture *cache = NULL;
  bool cache_is_outdated = false;
  Skin *the_skin = NULL;
  SDL_Cursor *cursor = NULL;
  std::vector<GUIContainer *> children;
  std::vector<GUIText *> texts;
  std::vector<GUIContainer *> get_children(float x, float y);

public:
  GUIContainer();
  GUIContainer(GUILayout layout);
  void set_skin(Skin *skin);
  void set_cursor(SDL_Cursor *cursor);
  void set_min_width(GUIUnit min_width);
  void set_min_height(GUIUnit min_height);
  void set_draggable(bool draggable);
  SDL_FRect get_bounding_rect() const;
  float get_width() const;
  float get_height() const;
  bool get_is_mouse_over() const;
  bool get_is_mouse_down() const;
  void update(float parent_width, float parent_height);
  void on_parent_resize(float new_parent_width, float new_parent_height);
  void add_container(GUIContainer *container);
  void add_text(GUIText *text);
  void update_cache(SDL_Renderer *renderer);
  void on_mouse_enter();
  void on_mouse_leave();
  void on_mouse_move(float x1, float y1, float x2, float y2);
  bool on_mouse_down(float x, float y);
  void on_mouse_up(float x, float y);
  void on_mouse_drag(float x, float y, float dx, float dy);
  void reset_focus();
  void reset_mouse();
  void render(SDL_Renderer *renderer, float parent_x, float parent_y);
};

#endif
