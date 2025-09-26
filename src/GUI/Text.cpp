#include <GUI/Text.hpp>

/*
GUIText::GUIText(std::string text, Font *font, SDL_Color color,
                 SDL_Color outline_color, GUIAlignment horizontal_alignment,
                 GUIAlignment vertical_alignment)
    : text(text), font(font), color(color), outline_color(outline_color),
      horizontal_alignment(horizontal_alignment),
      vertical_alignment(vertical_alignment) {
  texture = font->get_texture(text, color, outline_color, &w, &h);
}
*/

void GUIText::update(std::string text) {
  this->text = text;
  SDL_DestroyTexture(texture);
  texture = font->get_texture(text, color, outline_color, &w, &h);
}

void GUIText::render(SDL_Renderer *renderer, GUIContainer *parent) {
  const SDL_FRect parent_rect = parent->get_bounding_rect();
  // horizontal_alignment.calculate(parent_rect.w, w, &x);
  // vertical_alignment.calculate(parent_rect.h, h, &y);
  SDL_FRect dst = {(float)x,(float)y,w,h};
  SDL_RenderTexture(renderer, texture, NULL, &dst);
}
