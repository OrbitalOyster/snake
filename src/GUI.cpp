#include <GUI.hpp>
#include <SDL3/SDL_render.h>
#include <stdexcept>

GUI::GUI(SDL_Renderer *renderer) : renderer(renderer) {
  TTF_Init();
  create_cursors();
  root_container = new GUIContainer("root");
}

void GUI::create_cursors() {
  system_cursors["default"] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); /**< Default cursor. Usually an arrow. */
  system_cursors["text"] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_TEXT); /**< Text selection. Usually an I-beam. */
  system_cursors["wait"] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAIT); /**< Wait. Usually an hourglass or watch or spinning ball. */
  system_cursors["crosshair"] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR); /**< Crosshair. */
  system_cursors["progress"] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_PROGRESS); /**< Program is busy but still interactive. Usually it's WAIT with an arrow. */
  system_cursors["nwse_resize"] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NWSE_RESIZE); /**< Double arrow pointing northwest and southeast. */
  system_cursors["nesw_resize"] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NESW_RESIZE); /**< Double arrow pointing northeast and southwest. */
  system_cursors["ew_resize"] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_EW_RESIZE); /**< Double arrow pointing west and east. */
  system_cursors["ns_resize"] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NS_RESIZE); /**< Double arrow pointing north and south. */
  system_cursors["move"] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_MOVE); /**< Four pointed arrow pointing north, south, east, and west. */
  system_cursors["not_allowed"] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NOT_ALLOWED); /**< Not permitted. Usually a slashed circle or crossbones. */
  system_cursors["pointer"] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_POINTER); /**< Pointer that indicates a link. Usually a pointing hand. */
  system_cursors["nw_resize"] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE); /**< Window resize top-left. This may be a single arrow or a double arrow like NWSE_RESIZE. */
  system_cursors["n_resize"] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE); /**< Window resize top. May be NS_RESIZE. */
  system_cursors["ne_resize"] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE); /**< Window resize top-right. May be NESW_RESIZE. */
  system_cursors["e_resize"] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE); /**< Window resize right. May be EW_RESIZE. */
  system_cursors["se_resize"] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE); /**< Window resize bottom-right. May be NWSE_RESIZE. */
  system_cursors["s_resize"] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE); /**< Window resize bottom. May be NS_RESIZE. */
  system_cursors["sw_resize"] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE); /**< Window resize bottom-left. May be NESW_RESIZE. */
  system_cursors["w_resize"] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE); /**< Window resize left. May be EW_RESIZE. */
  system_cursors["count"] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_COUNT);
}

SDL_Cursor *GUI::get_system_cursor(std::string key) {
  if (!system_cursors.contains(key))
      throw std::runtime_error("System cursor not found: " + key);
  return system_cursors.at(key);
}

void GUI::add_container(GUIContainer *container) {
  root_container->add_container(container);
  container->on_resize(0, 0, root_container->get_width(),
                       root_container->get_height());
}

void GUI::add_text(GUIText *text) { root_container->add_text(text); }

void GUI::on_window_resize(unsigned width, unsigned height) {
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

void GUI::render() const { root_container->render(renderer); }
