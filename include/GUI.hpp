#ifndef GUI_HPP_
#define GUI_HPP_

#include <GUI/Container.hpp>
#include <GUI/Font.hpp>
#include <GUI/Text.hpp>
#include <Stretchable.hpp>

class GUI {
private:
  SDL_Renderer *renderer;
  GUIContainer *root_container;
  bool mouse_down = false;
  bool mouse_dragging = false;

public:
  GUI(SDL_Renderer *renderer);
  GUIContainer *get_root_container() const;
  void add_container(GUIContainer *container);
  void add_text(GUIText *text);
  void on_window_resize(unsigned width, unsigned height);
  void on_mouse_move(double x1, double y1, double x2, double y2);
  void on_mouse_down(double x, double y);
  void on_mouse_up(double x, double y);
  void on_mouse_drag(double x1, double y1, double x2, double y2);
  void reset_focus();
  void reset_mouse();
  void render() const;
  ~GUI();
};

#endif
