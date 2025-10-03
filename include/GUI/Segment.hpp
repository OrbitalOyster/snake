#ifndef GUI_SEGMENT_HPP_
#define GUI_SEGMENT_HPP_

#include <GUI/Unit.hpp>

/*
 * |<--------------------root_size----------------->|
 *                   |<-child_size->|
 * |-----------------|==============|---------------|
 * |-----size------->|
 */

class GUISegment {
private:
  GUIUnit size, start, end;

public:
  GUISegment(GUIUnit size = GUIUnit(0.0f), GUIUnit start = GUIUnit(),
             GUIUnit end = GUIUnit());
  bool depends_on_child_size();
  int calculate(int parent_size, int child_size);
  int calculate(int parent_size);
};

#endif
