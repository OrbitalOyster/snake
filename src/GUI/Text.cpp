#include <GUI/Text.hpp>

GUIText::GUIText(std::string text, Font *font, SDL_Color color,
                 SDL_Color outline_color, TextLayout layout)
    : text(text), font(font), color(color), outline_color(outline_color) {
  texture = font->get_texture(text, color, outline_color, &w, &h);
  this->layout = GUILayout((unsigned)w, (unsigned)h, layout.top, layout.left,
                           layout.bottom, layout.right);
}

void GUIText::update(std::string text) {
  this->text = text;
  SDL_DestroyTexture(texture);
  texture = font->get_texture(text, color, outline_color, &w, &h);
  /* TODO: Layout update */
}

void GUIText::render(SDL_Renderer *renderer, float parent_width,
                     float parent_height) {
  SDL_FRect dst = layout.calculate(parent_width, parent_height);
  // SDL_Log("%f %f %f %f %f %f", dst.x, dst.y, dst.w, dst.h, parent_width,
  // parent_height);
  SDL_RenderTexture(renderer, texture, NULL, &dst);
}
