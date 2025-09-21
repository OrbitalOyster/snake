#include <GUIUnit.hpp>
#include <stdexcept>

GUIUnit::GUIUnit(unsigned int l) {
  number.pixels = l;
  type = Pixels;
}

GUIUnit::GUIUnit(float l) {
  number.percent = l;
  type = Percent;
}

GUIUnit::GUIUnit() {}

bool GUIUnit::is_unset() { return type == Unset; }

bool GUIUnit::is_static() { return type == Pixels; }

unsigned int GUIUnit::to_pixels(unsigned int parent_length) {
  switch (type) {
  case Unset:
    return 0;
    break;
  case Pixels:
    return number.pixels;
    break;
  case Percent:
    return parent_length * number.percent;
    break;
  }
  /* Should not happen */
  throw std::runtime_error("Wut?!");
}
