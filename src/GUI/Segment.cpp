#include <GUI/Segment.hpp>
#include <stdexcept>
#include <iostream>

GUISegment::GUISegment(GUIUnit size, GUIUnit u1, GUIUnit u2)
    : size(size), u1(u1), u2(u2) {}

int GUISegment::calculate_offset(int root_size, int child_size) {
  int u1_p = u1.to_pixels(root_size);
  int target_size = size.to_pixels(root_size);
  int u2_p = u2.to_pixels(child_size);
  return u1_p + target_size - u2_p;
}

int GUISegment::calculate_size(int root_size) {
  int u1_p = u1.to_pixels(root_size);

  /* Unknown child width */
  if (!u2.is_static())
    throw std::runtime_error("Circular dependency");

  int u2_p = u2.to_pixels();

  return size.to_pixels(root_size) - u1_p + u2_p;

}
