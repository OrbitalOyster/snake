#include <GUI/Unit.hpp>
#include <stdexcept>

GUIUnit::GUIUnit(float number, GUIUnitType type) : number(number), type(type) {}

bool GUIUnit::is_absolute() const { return type == Relative; }

float GUIUnit::to_pixels() const {
  if (type != Absolute)
    throw std::runtime_error("Wrong!!!");
  return number;
}

float GUIUnit::to_pixels(float parent_length) const {
  switch (type) {
  case Relative:
    // SDL_Log("to pixels: %f %f %f", number, parent_length, number * parent_length);
    return parent_length * number;
    break;
  case Absolute:
    return number;
    break;
  }
  /* Should not happen */
  throw std::runtime_error("Wut?!");
}
