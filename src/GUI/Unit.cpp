#include <GUI/Unit.hpp>
#include <stdexcept>
#include <iostream>

GUIUnit::GUIUnit(unsigned int l) {
  number.pixels = l;
  type = Absolute;
}

GUIUnit::GUIUnit(float l) {
  number.percent = l;
  type = Relative;
}

bool GUIUnit::is_absolute() { return type == Absolute; }

int GUIUnit::to_pixels(unsigned int parent_length) {
  switch (type) {
  case Absolute:
    return number.pixels;
    break;
  case Relative:
    return parent_length * number.percent;
    break;
  }
  /* Should not happen */
  throw std::runtime_error("Wut?!");
}
