#ifndef GUI_CONTAINER_HPP_
#define GUI_CONTAINER_HPP_

#include <GUI/Layout.hpp>
#include <GUI/Segment.hpp>
#include <GUI/Skin.hpp>
#include <GUI/Text.hpp>
#include <GUI/Unit.hpp>
#include <Stretchable.hpp>
#include <string>
#include <vector>

class GUIContainer {
private:
  std::string tag;
  /* Layout */
  GUILayout layout;
  /* Actual dimensions */
  SDL_FRect rect;
  GUIUnit min_width, min_height;
  bool mouse_over = false;
  bool mouse_down = false;
  bool draggable = false;
  bool is_bubbling = true;
  /* Cache, updating on resize */
  SDL_Texture *cache = NULL;
  bool cache_is_outdated = false;
  Skin *skin = NULL;
  SDL_Cursor *cursor = NULL;
  std::vector<GUIContainer *> children;
  std::vector<GUIText *> texts;

public:
  GUIContainer(std::string tag);
  GUIContainer(std::string tag, GUILayout layout);
  std::string get_tag() const;
  std::vector<GUIContainer *> get_all_children();
  bool is_draggable();
  void set_skin(Skin *skin);
  void set_cursor(SDL_Cursor *cursor);
  void set_min_width(GUIUnit min_width);
  void set_min_height(GUIUnit min_height);
  void set_draggable(bool draggable);
  SDL_FRect get_bounding_rect() const;
  GUIContainer *find_child(double x, double y);
  void move(double dx, double dy);
  double get_width() const;
  double get_height() const;
  bool is_mouse_over() const;
  bool is_mouse_down() const;
  void on_resize(double parent_width, double parent_height);
  void add_container(GUIContainer *container);
  void add_text(GUIText *text);
  void update_cache(SDL_Renderer *renderer);
  void on_mouse_enter();
  void on_mouse_leave();
  void on_mouse_move(double x1, double y1, double x2, double y2);
  void on_mouse_down();
  void reset_mouse_down();
  void on_mouse_up();
  void on_mouse_click();
  void render(SDL_Renderer *renderer, double parent_x, double parent_y);
};

#endif
