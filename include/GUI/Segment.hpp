#ifndef GUI_SEGMENT_HPP
#define GUI_SEGMENT_HPP

#include <GUI/Unit.hpp>

class GUISegment {
private:
  GUIUnit u1;
  GUIUnit u2;
  GUIUnit size;

public:
  GUISegment(GUIUnit u1 = GUIUnit(0.0f), GUIUnit u2 = GUIUnit(0.0f), GUIUnit size = GUIUnit(0.0f));
  int calculate_offset(int root_size, int child_size);
  int calculate_size(int root_size);
};

#endif
