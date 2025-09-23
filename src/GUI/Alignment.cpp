#include "GUI/Unit.hpp"
#include <GUI/Alignment.hpp>

GUIAlignment::GUIAlignment() {}

GUIAlignment::GUIAlignment(GUIUnit u) : u(u) {}

GUIAlignment::GUIAlignment(GUIAlignmentType type) : type(type) {}

GUIAlignment::GUIAlignment(GUIUnit u, GUIAlignmentType type)
    : u(u), type(type) {}

GUIAlignment::GUIAlignment(GUIUnit u, GUIAlignmentType type, GUIUnit offset)
    : u(u), type(type), offset(offset) {}

void GUIAlignment::calculate(int root_size, int s, int *l) {
  switch (type) {
  case Start:
    *l = u.to_pixels(root_size) + offset.to_pixels(s);
    break;
  case End:
    *l = root_size - s - u.to_pixels(root_size) - offset.to_pixels(s);
    break;
  }
}
