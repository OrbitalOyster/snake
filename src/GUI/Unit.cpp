#include <GUI/Unit.hpp>
#include <stdexcept>

GUIUnit::GUIUnit(double number, GUIUnitType type) : number(number), type(type) {}

bool GUIUnit::is_absolute() const { return type == Absolute; }

double GUIUnit::to_pixels() const {
  if (type != Absolute)
    throw std::runtime_error("Wrong!!!");
  return number;
}

double GUIUnit::to_pixels(double parent_length) const {
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
