#include <GUI/Alignment.hpp>

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
