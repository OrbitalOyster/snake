#include "GUIUnit.hpp"
#include <GUISizing.hpp>
#include <stdexcept>

GUISizing::GUISizing() {
  u1 = GUIUnit(0u);
  u2 = GUIUnit();
  u3 = GUIUnit(0u);
}

GUISizing::GUISizing(GUIUnit u1, GUIUnit u2, GUIUnit u3)
    : u1(u1), u2(u2), u3(u3) {
  if (u1.is_computable() + u2.is_computable() + u3.is_computable() != 1)
    throw std::runtime_error("GUI error (computables =/= 1)");
}

void GUISizing::calculate(float root_size, float *l, float *s) {
  int u1p = 0, u2p = 0;

  if (u1.is_computable())
    u1p = root_size - u2.to_pixels(root_size) - u3.to_pixels(root_size);
  else
    u1p = u1.to_pixels(root_size);

  if (u2.is_computable())
    u2p = root_size - u1.to_pixels(root_size) - u3.to_pixels(root_size);
  else
    u2p = u2.to_pixels(root_size);

  *l = u1p;
  *s = u2p;
}
