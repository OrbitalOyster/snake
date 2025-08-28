#include <Label.hpp>

Label::Label(std::string text) : text(text) {

}

void Label::set_text(std::string new_text) {
  text = new_text;
}
