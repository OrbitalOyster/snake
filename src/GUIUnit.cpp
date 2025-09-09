#include <GUIUnit.hpp>
#include <stdexcept>

GUIUnit::GUIUnit(unsigned int l) {
  pixels = l;
  type = Pixels;
}

GUIUnit::GUIUnit(float l) {
  percent = l;
  type = Percent;
}

GUIUnit::GUIUnit() {}

bool GUIUnit::is_computable() {
    return type == Computable;
}

unsigned int GUIUnit::to_pixels(unsigned int parent_length) {
  switch (type) {
  case Computable:
    throw std::runtime_error("GUI Error 1");
    break;
  case Pixels:
    return pixels;
    break;
  case Percent:
    return parent_length * percent;
    break;
  }
}
