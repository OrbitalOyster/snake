#include <GUI/Segment.hpp>
#include <GUI/Unit.hpp>
#include <stdexcept>

GUISegment::GUISegment(GUIUnit size, GUIUnit start, GUIUnit end)
    : size(size), start(start), end(end) {}

bool GUISegment::depends_on_child_size() const { return !end.is_absolute(); }

bool GUISegment::is_resizable() const { return size.is_absolute(); }

void GUISegment::resize(double delta) {
  size = GUIUnit(size.to_pixels() + delta, Absolute);
}

double GUISegment::calculate(double parent_size, double child_size) const {
  return start.to_pixels(parent_size) + size.to_pixels(parent_size) -
         end.to_pixels(child_size);
}

double GUISegment::calculate(double parent_size) const {
  /* Unknown child size */
  if (depends_on_child_size())
    throw std::runtime_error("Circular dependency");
  return start.to_pixels(parent_size) + size.to_pixels(parent_size);
}
