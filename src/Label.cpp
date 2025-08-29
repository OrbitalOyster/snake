#include <Label.hpp>

Label::Label(std::string text, float x, float y, Font *font, SDL_Color color,
             SDL_Color outline_color)
    : text(text), x(x), y(y), font(font) {
  texture = font->render_text(text, color, outline_color, &width, &height);
}

void Label::set_text(std::string new_text) {
  text = new_text;
}

SDL_FRect Label::get_bounding_rect() const { return {x, y, width, height}; }
