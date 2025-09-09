#include "GUISizing.hpp"
#include "GUIUnit.hpp"
#include <Container.hpp>
#include <iostream>
#include <stdexcept>

Container::Container() {}

void Container::set_horizontal_sizing(GUIUnit left, GUIUnit width,
                                      GUIUnit right) {
  unsigned computables = 0;
  computables += left.is_computable();
  computables += width.is_computable();
  computables += right.is_computable();
  if (computables != 1)
    throw std::runtime_error("GUI error (computables =/= 1)");

  u_left = left;
  u_width = width;
  u_right = right;
}

void Container::set_horizontal_sizing(GUIUnit left, GUIUnit width,
                                      GUIUnit right, GUIUnit offset_left) {
  unsigned computables = 0;

  /* Can't have left and width depend on each other */
  if (width.is_computable() && !offset_left.is_static())
    throw std::runtime_error("GUI error (left => width => left)");

  if (left.is_computable())
    throw std::runtime_error("GUI debug error");

  computables += left.is_computable();
  computables += width.is_computable();
  computables += right.is_computable();
  if (computables != 1)
    throw std::runtime_error("GUI error (computables =/= 1)");

  u_left = left;
  u_width = width;
  u_right = right;

  u_offset_left = offset_left;
}

void Container::set_vertical_sizing(GUISizing sizing) {
  vertical_sizing = sizing;
}

void Container::set_vertical_sizing(GUIUnit top, GUIUnit height,
                                    GUIUnit bottom) {
  unsigned computables = 0;
  computables += top.is_computable();
  computables += height.is_computable();
  computables += bottom.is_computable();
  if (computables != 1)
    throw std::runtime_error("GUI error (computables =/= 1)");

  u_top = top;
  u_height = height;
  u_bottom = bottom;
}

SDL_FRect Container::get_bounding_rect() const { return {x, y, w, h}; }

float Container::get_width() const { return w; }

float Container::get_height() const { return h; }

void Container::update(float parent_width, float parent_height) {

  /* TODO: So much lunacy */
  int u1 = -1, u2 = -1, u3 = -1;
  if (!u_left.is_computable())
    u1 = u_left.to_pixels(parent_width);
  if (!u_width.is_computable())
    u2 = u_width.to_pixels(parent_width);
  if (!u_right.is_computable())
    u3 = u_right.to_pixels(parent_width);

  if (u_left.is_computable())
    u1 = parent_width - u2 - u3;
  if (u_width.is_computable())
    u2 = parent_width - u1 - u3;
  if (u_right.is_computable())
    u3 = parent_width - u1 - u2;

  x = u1;
  w = u2;

  int offset_left_p = 0;
  if (!u_offset_left.is_computable())
    offset_left_p = u_offset_left.to_pixels(w);
  x += offset_left_p;
  std::cout << offset_left_p << std::endl;

  /*
    int u4 = -1, u5 = -1, u6 = -1;
    if (!u_top.is_computable())
      u4 = u_top.to_pixels(parent_height);
    if (!u_height.is_computable())
      u5 = u_height.to_pixels(parent_height);
    if (!u_bottom.is_computable())
      u6 = u_bottom.to_pixels(parent_height);

    if (u_top.is_computable())
      u4 = parent_height - u5 - u6;
    if (u_height.is_computable())
      u5 = parent_height - u4 - u6;
    if (u_bottom.is_computable())
      u6 = parent_height - u4 - u5;

    y = u4;
    h = u5;
  */

  vertical_sizing.calculate(parent_height, &y, &h);

  for (Container *c : children) {
    c->update(w, h);
  }
}

void Container::add_container(Container *container) {
  children.push_back(container);
  children.back()->update(w, h);
}

void Container::render(SDL_Renderer *renderer) {
  const SDL_FRect dst = get_bounding_rect();
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0, 0xFF);
  SDL_RenderRect(renderer, &dst);

  for (Container *c : children) {
    c->render(renderer);
  }
}
