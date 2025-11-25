#ifndef GUI_UNIT_HPP_
#define GUI_UNIT_HPP_

enum GUIUnitType { Absolute, Relative };

class GUIUnit {
private:
  float number;
  enum GUIUnitType type;

public:
  GUIUnit(float number = 0, GUIUnitType type = Absolute);
  bool is_absolute() const;
  float to_pixels() const;
  float to_pixels(float parent_length) const;
};

#endif
