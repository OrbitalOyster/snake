#ifndef GUI_UNIT_HPP_
#define GUI_UNIT_HPP_

class GUIUnit {
private:
  enum GUIUnitType { Absolute, Relative };
  GUIUnitType type;
  union GUIUnitNumber {
    unsigned int pixels;
    float percent;
  };
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
