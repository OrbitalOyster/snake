#include <GUI/Unit.hpp>
#include <stdexcept>

GUIUnit::GUIUnit() {}

GUIUnit::GUIUnit(unsigned int l) {
  number.pixels = l;
  type = Pixels;
}

GUIUnit::GUIUnit(float l) {
  number.percent = l;
  type = Percent;
}

// bool GUIUnit::is_unset() { return type == Unset; }

bool GUIUnit::is_static() { return type == Pixels; }

/* For static units */
unsigned int GUIUnit::to_pixels() {
  if (type != Pixels)
    throw std::runtime_error("Wrong!!");
  return number.pixels;
}

unsigned int GUIUnit::to_pixels(unsigned int parent_length) {
  switch (type) {
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
