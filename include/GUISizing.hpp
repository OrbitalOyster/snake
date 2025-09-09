#ifndef GUI_SIZING_HPP
#define GUI_SIZING_HPP

#include <GUIUnit.hpp>

class GUISizing {
private:
  GUIUnit u1, u2, u3;

public:
  GUISizing();
  GUISizing(GUIUnit u1, GUIUnit u2, GUIUnit u3);
  void calculate(float root_size, float *l, float *s);
};

#endif
