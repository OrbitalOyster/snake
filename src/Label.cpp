#include <Label.hpp>

Label::Label(std::string text, float x, float y) : text(text), x(x), y(y) {
  texture = NULL;
}

void Label::set_text(std::string new_text) { text = new_text; }
