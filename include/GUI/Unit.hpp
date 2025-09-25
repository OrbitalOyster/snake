#ifndef GUI_UNIT_HPP_
#define GUI_UNIT_HPP_

enum GUIUnitType { Pixels, Percent, Unset };
union GUIUnitNumber {
  unsigned int pixels;
  float percent;
};

class GUIUnit {
private:
  GUIUnitType type = Unset;
  GUIUnitNumber number;
public:
  /* Computable */
  GUIUnit();
  /* Absolute, pixels */
  GUIUnit(unsigned int l);
  /* Relative, percents */
  GUIUnit(float l);
  bool is_unset();
  bool is_static();
  unsigned int to_pixels();
  unsigned int to_pixels(unsigned int parent_length);
};

#endif
