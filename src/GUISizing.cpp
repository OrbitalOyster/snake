#include <GUISizing.hpp>
#include <stdexcept>

GUISizing::GUISizing() {
  u1 = GUIUnit(0u);
  u2 = GUIUnit();
  u3 = GUIUnit(0u);
}

GUISizing::GUISizing(GUIUnit u1, GUIUnit u2, GUIUnit u3)
    : u1(u1), u2(u2), u3(u3) {
  if (u1.is_unset() + u2.is_unset() + u3.is_unset() != 1)
    throw std::runtime_error("GUI error (computables =/= 1)");
}

GUISizing::GUISizing(GUIUnit u1, GUIUnit u2, GUIUnit u3, GUIUnit offset)
    : u1(u1), u2(u2), u3(u3), offset(offset) {
  if (u1.is_unset() + u2.is_unset() + u3.is_unset() != 1)
    throw std::runtime_error("GUI error (computables =/= 1)");

  if (u2.is_unset() && !offset.is_static())
    throw std::runtime_error("GUI Error (u1/u3 => u2 => u1/u3 => ...)");
}

void GUISizing::calculate(int root_size, int *l, int *s) {
  if (u1.is_unset())
    *l = root_size - u2.to_pixels(root_size) - u3.to_pixels(root_size);
  else
    *l = u1.to_pixels(root_size);

  if (u2.is_unset())
    *s = root_size - u1.to_pixels(root_size) - u3.to_pixels(root_size);
  else
    *s = u2.to_pixels(root_size);

  if (u1.is_unset())
    *l -= offset.to_pixels(*s);
  else
    *l += offset.to_pixels(*s);
}
