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
  bool mouse_over = false;
  bool mouse_down = false;
  bool mouse_dragging = false;
  bool is_draggable = false;
  bool is_bubbling = true;
  /* Cache, updating on resize */
  SDL_Texture *cache = NULL;
  bool cache_is_outdated = false;
  Skin *skin = NULL;
  SDL_Cursor *cursor = NULL;
  std::vector<GUIContainer *> children;
  std::vector<GUIText *> texts;
  std::vector<GUIContainer *> get_children(double x, double y);

public:
  GUIContainer();
  GUIContainer(GUILayout layout);
  void set_skin(Skin *skin);
  void set_cursor(SDL_Cursor *cursor);
  void set_min_width(GUIUnit min_width);
  void set_min_height(GUIUnit min_height);
  void set_draggable(bool draggable);
  SDL_FRect get_bounding_rect() const;
  double get_width() const;
  double get_height() const;
  bool is_mouse_over() const;
  bool is_mouse_down() const;
  void on_resize(double parent_width, double parent_height);
  void add_container(GUIContainer *container);
  void add_text(GUIText *text);
  void update_cache(SDL_Renderer *renderer);
  void on_mouse_enter(double x, double y);
  void on_mouse_leave();
  void on_mouse_move(double x1, double y1, double x2, double y2);
  bool on_mouse_down(double x, double y);
  void on_mouse_up(double x, double y);
  void on_mouse_click();
  //  void on_mouse_drag(double x, double y, double dx, double dy);
  //  void reset_focus();
  void reset_mouse();
  void render(SDL_Renderer *renderer, double parent_x, double parent_y);
};

#endif
