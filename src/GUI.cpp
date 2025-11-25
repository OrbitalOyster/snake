#include <GUI.hpp>
#include <SDL3/SDL_render.h>

GUI::GUI(SDL_Renderer *renderer) : renderer(renderer) {
  TTF_Init();
  root_container = new GUIContainer();
}

void GUI::add_container(GUIContainer *container) {
  root_container->add_container(container);
  SDL_Cursor *defaultCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
  root_container->set_cursor(defaultCursor);
  container->update(root_container->get_width(), root_container->get_height());
}

void GUI::add_text(GUIText *text) { root_container->add_text(text); }

void GUI::on_window_resize(int width, int height) {
  root_container->update(width, height);
}

void GUI::on_mouse_move(float x1, float y1, float x2, float y2) {
  root_container->on_mouse_move(x1, y1, x2, y2);
}

void GUI::on_mouse_down(float x, float y) {
  root_container->on_mouse_down(x, y);
}

void GUI::on_mouse_up(float x, float y) { root_container->on_mouse_up(x, y); }

void GUI::on_mouse_drag(float x1, float y1, float x2, float y2) {
  root_container->on_mouse_drag(x1, y1, x2 - x1, y2 - y1);
  // root_container->update(root_container->get_width(), root_container->get_height());
}

void GUI::reset_focus() { root_container->reset_focus(); }

void GUI::render() const { root_container->render(renderer, 0, 0); }
