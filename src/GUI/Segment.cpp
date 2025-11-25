#include <GUI/Segment.hpp>
#include <cstdio>
#include <stdexcept>

GUISegment::GUISegment(GUIUnit size, GUIUnit start, GUIUnit end)
    : size(size), start(start), end(end) {}

bool GUISegment::depends_on_child_size() const { return !end.is_absolute(); }

bool GUISegment::is_resizable() const { return size.is_absolute(); }

void GUISegment::resize(float delta) {
  // std::printf(">>> %d\n", size.to_pixels());
  size = GUIUnit(size.to_pixels() + delta);
}

float GUISegment::calculate(float parent_size, float child_size) const {
  return start.to_pixels(parent_size) + size.to_pixels(parent_size) -
         end.to_pixels(child_size);
}

float GUISegment::calculate(float parent_size) const {
  /* Unknown child size */
  if (depends_on_child_size())
    throw std::runtime_error("Circular dependency");
  /* "child_size" is irrelevant for absolute units */
  return calculate(parent_size, 800865);
}

float GUISegment::get_absolute_size() const {
  if (!size.is_absolute())
    throw std::runtime_error("Wrong!");
  return size.to_pixels();
}
