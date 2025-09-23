#ifndef GUI_ALIGNMENT_HPP
#define GUI_ALIGNMENT_HPP

#include <GUI/Unit.hpp>

enum GUIAlignmentType { Start, End };

class GUIAlignment {
private:
  GUIUnit u = GUIUnit(0u);
  GUIAlignmentType type = Start;
  GUIUnit offset = GUIUnit();

public:
  GUIAlignment();
  GUIAlignment(GUIUnit u);
  GUIAlignment(GUIAlignmentType type);
  GUIAlignment(GUIUnit u, GUIAlignmentType type);
  GUIAlignment(GUIUnit u, GUIAlignmentType type, GUIUnit offset);
  void calculate(int root_size, int s, int *l);
};

#endif
