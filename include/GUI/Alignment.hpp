#ifndef GUI_ALIGNMENT_HPP_
#define GUI_ALIGNMENT_HPP_

#include <GUI/Unit.hpp>

enum GUIAlignmentType { Start, End };

/*
 *         u
 *  |-------------->
 *  /----------|-------|------------/
 *  Start       <--s-->           End
 *
 *  <----------root_size------------>
 */

class GUIAlignment {
private:
  GUIUnit u = 0u;
  GUIAlignmentType type = Start;
  GUIUnit offset;

public:
  GUIAlignment(GUIUnit u = 0u, GUIAlignmentType type = Start, GUIUnit offset = 0u);
  void calculate(int root_size, int s, int *l);
};

#endif
