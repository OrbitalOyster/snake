#include <GUI.hpp>
#include <SDL3/SDL_render.h>

GUI::GUI(SDL_Renderer *renderer) : renderer(renderer) {
  TTF_Init();
  root_container = new GUIContainer();
}

void GUI::add_container(GUIContainer *container) {
  root_container->add_container(container);
  container->on_resize(root_container->get_width(),
                       root_container->get_height());
}

void GUI::add_text(GUIText *text) { root_container->add_text(text); }

void GUI::on_window_resize(double width, double height) {
  root_container->on_resize(width, height);
}

void GUI::on_mouse_move(double x1, double y1, double x2, double y2) {
  root_container->on_mouse_move(x1, y1, x2, y2);
}

void GUI::on_mouse_down(double x, double y) {
  root_container->on_mouse_down(x, y);
}

void GUI::on_mouse_up(double x, double y) { root_container->on_mouse_up(x, y); }

void GUI::on_mouse_drag(double x1, double y1, double x2, double y2) {
  root_container->on_mouse_drag(x1, y1, x2 - x1, y2 - y1);
}

void GUI::reset_focus() { root_container->on_mouse_leave(); }

void GUI::render() const { root_container->render(renderer, 0, 0); }
