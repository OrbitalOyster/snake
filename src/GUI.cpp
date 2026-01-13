#include <GUI.hpp>
#include <SDL3/SDL_render.h>

GUI::GUI(SDL_Renderer *renderer) : renderer(renderer) {
  TTF_Init();
  root_container = new GUIContainer("root");
}

void GUI::add_container(GUIContainer *container) {
  root_container->add_container(container);
  container->on_resize(0, 0, root_container->get_width(),
                       root_container->get_height());
}

void GUI::add_text(GUIText *text) { root_container->add_text(text); }

void GUI::on_window_resize(double width, double height) {
  root_container->on_resize(0, 0, width, height);
  reset_mouse();
}

void GUI::on_mouse_move(double x1, double y1, double x2, double y2) {
  GUIContainer *child1 = root_container->find_child(x1, y1);
  GUIContainer *child2 = root_container->find_child(x2, y2);
  /* Dragging */
  if (mouse_dragging && child1) {
    child1->move(x2 - x1, y2 - y1);
    return;
  }
  /* Mouse within one child */
  if (child1 == child2)
    return;
  /* Left child1 */
  if (child1)
    child1->on_mouse_leave();
  /* Entered child2 */
  if (child2)
    child2->on_mouse_enter();
}

void GUI::on_mouse_down(double x, double y) {
  GUIContainer *child = root_container->find_child(x, y);
  if (child->is_draggable() && !mouse_dragging)
    mouse_dragging = true;
  child->on_mouse_down();
}

void GUI::on_mouse_up(double x, double y) {
  GUIContainer *mouse_over_child = root_container->find_child(x, y);
  mouse_over_child->on_mouse_up();
  /* Reset all mouse_down children */
  if (root_container->is_mouse_down())
    root_container->reset_mouse_down();
  for (GUIContainer *child : root_container->get_all_children())
    if (child->is_mouse_down())
      child->reset_mouse_down();
  /* Reset dragging */
  if (mouse_dragging)
    mouse_dragging = false;
}

void GUI::reset_focus() { root_container->on_mouse_leave(); }

void GUI::reset_mouse() {
  float x = 0, y = 0;
  SDL_GetMouseState(&x, &y);
  /* Handle mouse over container */
  GUIContainer *mouse_over_child = root_container->find_child(x, y);
  if (!mouse_over_child->is_mouse_over())
    mouse_over_child->on_mouse_enter();
  /*  Handle the rest */
  std::vector<GUIContainer *> children = root_container->get_all_children();
  for (GUIContainer *child : children)
    if (child != mouse_over_child && child->is_mouse_over())
      child->on_mouse_leave();
}

void GUI::render() const { root_container->render(renderer, 0, 0); }
