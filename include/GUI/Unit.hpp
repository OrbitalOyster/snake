#ifndef GUI_UNIT_HPP_
#define GUI_UNIT_HPP_

enum GUIUnitType { Pixels, Percent };
union GUIUnitNumber {
  unsigned int pixels;
  float percent;
};

class GUIUnit {
private:
  GUIUnitType type;
  GUIUnitNumber number;

public:
  /* Absolute, pixels */
  GUIUnit(unsigned int l = 0u);
  /* Relative, percents */
  GUIUnit(float l);
  bool is_absolute();
  unsigned int to_pixels(unsigned int parent_length);
};

#endif
