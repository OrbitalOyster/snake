#include <GUI/Segment.hpp>
#include <stdexcept>

GUISegment::GUISegment(GUIUnit size, GUIUnit start, GUIUnit end)
    : size(size), start(start), end(end) {}

/*
 * |                      |
 * |<--start-->|          |<---end-->|
 * |           |==========|=========>|
 * |           |<-------size-------->|
 * |<---calculate()------>|
 * |                      |
 */
int GUISegment::calculate(int parent_size, int child_size) {
  return start.to_pixels(parent_size) + size.to_pixels(parent_size) -
         end.to_pixels(child_size);
}

int GUISegment::calculate(int parent_size) {
  /* Unknown child size */
  if (!end.is_absolute())
    throw std::runtime_error("Circular dependency");
  /* "child_size" is irrelevant for absolute units */
  return calculate(parent_size, 800865);
}
