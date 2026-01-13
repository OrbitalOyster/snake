#include <GUI/Unit.hpp>
#include <stdexcept>

GUIUnit::GUIUnit(double value, GUIUnitType type) : value(value), type(type) {}

bool GUIUnit::is_absolute() const { return type == Absolute; }

double GUIUnit::to_pixels() const {
  if (type != Absolute)
    throw std::runtime_error("Wrong!!!");
  return value;
}

double GUIUnit::to_pixels(double parent_length) const {
  switch (type) {
  case Relative:
    return parent_length * value;
  case Absolute:
    return value;
  }
  /* Should not happen */
  throw std::runtime_error("Wut?!");
}
