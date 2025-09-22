#ifndef GUI_SIZING_HPP
#define GUI_SIZING_HPP

#include <GUI/Unit.hpp>

class GUISizing {
private:
  GUIUnit u1, u2, u3;
  GUIUnit offset;

public:
  GUISizing();
  GUISizing(GUIUnit u1, GUIUnit u2, GUIUnit u3);
  GUISizing(GUIUnit u1, GUIUnit u2, GUIUnit u3, GUIUnit offset);
  void calculate(int root_size, int *l, int *s);
};

#endif
