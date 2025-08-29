#include <Label.hpp>
#include <SDL3/SDL_render.h>

Label::Label(std::string text, float x, float y, Font *font, SDL_Color color,
             SDL_Color outline_color)
    : text(text), x(x), y(y), font(font), color(color),
      outline_color(outline_color) {
  set_text(text);
}

void Label::render() {
  SDL_DestroyTexture(texture);
  texture = font->get_texture(text, color, outline_color, &width, &height);
}

void Label::set_text(std::string new_text) {
  text = new_text;
  render();
}

SDL_FRect Label::get_bounding_rect() const { return {x, y, width, height}; }

SDL_Texture *Label::get_texture() const { return texture; }

Label::~Label() { SDL_DestroyTexture(texture); }
