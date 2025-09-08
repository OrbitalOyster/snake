#ifndef GUI_UNIT_HPP_
#define GUI_UNIT_HPP_

enum GUIUnitType { Pixels, Percent, Computable };

class GUIUnit {
private:
  GUIUnitType type = Computable;
  unsigned int pixels;
  float percent;

public:
  /* Computable */
  GUIUnit();
  /* Absolute, pixels */
  GUIUnit(unsigned int l);
  /* Relative, percents */
  GUIUnit(float l);
  unsigned int to_pixels(unsigned int parent_length);
};

#endif
