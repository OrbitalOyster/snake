#include "SDL3/SDL_log.h"
#include <GUI/Layout.hpp>
#include <stdexcept>

GUILayout::GUILayout(std::optional<GUIUnit> width,
                     std::optional<GUIUnit> height,
                     std::optional<GUISegment> left,
                     std::optional<GUISegment> top,
                     std::optional<GUISegment> right,
                     std::optional<GUISegment> bottom)
    : width(width), height(height), left(left), top(top), right(right),
      bottom(bottom) {
  /* Horizontal axis */
  if (width.has_value()) { /* Known width */
    if (left.has_value() && right.has_value())
      throw std::runtime_error("Redundant horizontal axis values");
    if (!left.has_value() && !right.has_value())
      throw std::runtime_error("Missing left and right alignments");
  } else { /* Unknown width */
    if (!left.has_value())
      throw std::runtime_error("Missing left alignment");
    if (!right.has_value())
      throw std::runtime_error("Missing right alignment");
    if (left.value().depends_on_child_size())
      throw std::runtime_error("Circular dependency (left)");
    if (right.value().depends_on_child_size())
      throw std::runtime_error("Circular dependency (right)");
  }
  /* Vertical axis */
  if (height.has_value()) { /* Known width */
    if (top.has_value() && bottom.has_value())
      throw std::runtime_error("Redundant vertical axis values");
    if (!top.has_value() && !bottom.has_value())
      throw std::runtime_error("Missing top and bottom alignments");
  } else { /* Unknown height */
    if (!top.has_value())
      throw std::runtime_error("Missing top alignment");
    if (!bottom.has_value())
      throw std::runtime_error("Missing bottom alignment");
    if (top.value().depends_on_child_size())
      throw std::runtime_error("Circular dependency (top)");
    if (bottom.value().depends_on_child_size())
      throw std::runtime_error("Circular dependency (bottom)");
  }
}

GUILayout::GUILayout() {
  width = GUIUnit(1.0f);
  height = GUIUnit(1.0f);
  top = GUISegment();
  left = GUISegment();
}

/* a.k.a "movable layout" */
GUILayout::GUILayout(GUIUnit width, GUIUnit height, GUISegment left,
                     GUISegment top)
    : width(width), height(height), left(left), top(top) {}

/* Unknown size */
GUILayout::GUILayout(GUISegment left, GUISegment top, GUISegment right,
                     GUISegment bottom)
    : GUILayout({}, {}, left, top, right, bottom) {}

/* Top-left */
GUILayout::GUILayout(GUISegment left, GUISegment top)
    : GUILayout({}, {}, left, top, {}, {}) {};

double GUILayout::get_left() { return left->get_absolute_size(); }

void GUILayout::move(double dx, double dy) {
  // SDL_Log("Moving container %f %f", dx, dy);
  // left->debug();
  left->resize(dx);
  top->resize(dy);
}

SDL_FRect GUILayout::calculate(double parent_width, double parent_height) {
  double x, y, w, h;
  /* Known width */
  if (width.has_value()) {
    w = width->to_pixels(parent_width);
    if (left.has_value()) {
      x = left->calculate(parent_width, w);
    } else {
      double right_p = right->calculate(parent_width, w);
      x = parent_width - w - right_p;
    }
  } else { /* Unknown width */
    x = left->calculate(parent_width);
    double right_p = right->calculate(parent_width);
    w = parent_width - x - right_p;
  }
  /* Known height */
  if (height.has_value()) {
    h = height->to_pixels(parent_height);
    if (top.has_value()) {
      y = top->calculate(parent_height, h);
    } else {
      double bottom_p = bottom->calculate(parent_height, h);
      y = parent_height - h - bottom_p;
    }
  } else { /* Unknown height */
    y = top->calculate(parent_height);
    double bottom_p = bottom->calculate(parent_height);
    h = parent_height - y - bottom_p;
  }
  /* Done */
  // SDL_Log("Layout calculated %f %f %f %f / %f %f", x, y, w, h, parent_width,
  // parent_height);
  return {(float)x, (float)y, (float)w, (float)h};
}
