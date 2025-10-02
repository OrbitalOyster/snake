#include <GUI.hpp>
#include <SDL3/SDL_render.h>

GUI::GUI(SDL_Renderer *renderer) : renderer(renderer) {
  TTF_Init();
  root_container = new GUIContainer();
}

void GUI::add_container(GUIContainer *container) {
  root_container->add_container(container);
  container->update(root_container->get_width(), root_container->get_height());
}

void GUI::add_text(GUIText *text) { texts.push_back(text); }

void GUI::on_window_resize(int width, int height) {
  root_container->update(width, height);
}

void GUI::render() const {
  root_container->render(renderer, 0, 0);
  for (GUIText *t : texts)
    t->render(renderer, root_container);
}
