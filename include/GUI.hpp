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

public:
  GUI(SDL_Renderer *renderer);
  GUIContainer *get_root_container() const;
  void add_container(GUIContainer *container);
  void add_text(GUIText *text);
  void on_window_resize(float width, float height);
  void on_mouse_move(float x1, float y1, float x2, float y2);
  void on_mouse_down(float x, float y);
  void on_mouse_up(float x, float y);
  void on_mouse_drag(float x1, float y1, float x2, float y2);
  void reset_focus();
  void render() const;
  ~GUI();
};

#endif
