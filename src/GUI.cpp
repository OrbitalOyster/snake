#include "SDL3/SDL_log.h"
#include <GUI.hpp>
#include <SDL3/SDL_render.h>

GUI::GUI(SDL_Renderer *renderer) : renderer(renderer) {
  TTF_Init();
  root_container = new GUIContainer("root");
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
  GUIContainer *child1 = root_container->find_child(x1, y1);
  GUIContainer *child2 = root_container->find_child(x2, y2);

  /* No children involved */
  if (!child1 && !child2) {
    return;
  }

  if (mouse_dragging) {
    SDL_Log("Mouse dragging");
    if (child1) {
      child1->move(x2 - x1, y2 - y1);
      child1 = root_container->find_child(x1, y1);
      child2 = root_container->find_child(x2, y2);
    }
  }

  /* Mouse within one child */
  if (child1 == child2) {
    // child1.back()->on_mouse_move(x1, y1, x2, y2);
    return;
  }

  /* Left child1 */
  if (child1) {
    child1->on_mouse_leave();
    // if (child2.empty())
    //  on_mouse_enter(x2, y2);
  }

  /* Entered child2 */
  if (child2) {
    // on_mouse_leave();
    child2->on_mouse_enter(x2, y2);
  }
}

void GUI::on_mouse_down(double x, double y) {
  // root_container->on_mouse_down(x, y);
  GUIContainer *child = root_container->find_child(x, y);
  if (child == root_container)
    return;

  if (child->is_draggable() && !mouse_dragging)
    mouse_dragging = true;

  // SDL_Log("Mouse down: %s", child->get_tag().c_str());
  child->on_mouse_down(x, y);
}

void GUI::on_mouse_up(double x, double y) {
  for (GUIContainer *child : root_container->get_all_children())
    if (child->is_mouse_down())
      child->on_mouse_up(x, y);

  if (mouse_dragging)
    mouse_dragging = false;

  // GUIContainer *child = root_container->find_child(x, y);
  // if (child == root_container)
  //   return;

  // SDL_Log("Mouse up: %s", child->get_tag().c_str());
  // child->on_mouse_up(x, y);
  // root_container->on_mouse_up(x, y);
}

//void GUI::on_mouse_drag(double x1, double y1, double x2, double y2) {
  // root_container->on_mouse_drag(x1, y1, x2 - x1, y2 - y1);
//}

void GUI::reset_focus() { root_container->on_mouse_leave(); }

void GUI::reset_mouse() { root_container->reset_mouse(); }

void GUI::render() const { root_container->render(renderer, 0, 0); }
