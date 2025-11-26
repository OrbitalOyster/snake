#ifndef GUI_UNIT_HPP_
#define GUI_UNIT_HPP_

enum GUIUnitType { Relative, Absolute };

class GUIUnit {
private:
  double number;
  enum GUIUnitType type;

public:
  GUIUnit(double number = 0, GUIUnitType type = Relative);
  bool is_absolute() const;
  double to_pixels() const;
  double to_pixels(double parent_length) const;
};

#endif
