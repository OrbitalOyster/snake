#include <GUI/Segment.hpp>
#include <stdexcept>

GUISegment::GUISegment(GUIUnit size, GUIUnit u1, GUIUnit u2)
    : size(size), start(u1), end(u2) {}

/*
 * |-start-|----------------|=========> end
 * |<-------offset--------->|
 */
int GUISegment::calculate(int parent_size, int child_size) {
  return start.to_pixels(parent_size) + size.to_pixels(parent_size) -
         end.to_pixels(child_size);
}

int GUISegment::calculate(int parent_size) {
  /* Unknown child size */
  if (!end.is_absolute())
    throw std::runtime_error("Circular dependency");
  return calculate(parent_size,
                   800865); /* "child size" is irrelevant for absolute units */
}
