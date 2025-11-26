#ifndef GUI_SEGMENT_HPP_
#define GUI_SEGMENT_HPP_

#include <GUI/Unit.hpp>

/*
 * |<----------------------parent_size--------------------->|
 * |                                                        |
 * |<-start->|<---------size------->|                       |
 * |                 |<-----end---->|                       |
 * |                 |==============|============|          |
 * |                 |<-------child_size-------->|          |
 * |<--calculate()-->|                                      |
 */

/* Refer to ASCHII art */
class GUISegment {
private:
  GUIUnit size, start, end;

public:
  void debug();
  GUISegment(GUIUnit size = GUIUnit(),
             GUIUnit start = GUIUnit(),
             GUIUnit end = GUIUnit(0, Absolute));
  bool depends_on_child_size() const;
  double calculate(double parent_size, double child_size) const;
  double calculate(double parent_size) const;
  bool is_resizable() const;
  void resize(double delta);
  double get_absolute_size() const;
};

#endif
