#include <GUI/Text.hpp>
#include <cmath>

GUIText::GUIText(std::string text, Font *font, SDL_Color color,
                 SDL_Color outline_color, TextLayout text_layout)
    : text(text), font(font), color(color), outline_color(outline_color) {
  texture = font->get_texture(text, color, outline_color, &width, &height);
  // SDL_Log("width height %f %f", width, height);
  layout = GUILayout(GUIUnit(width, Absolute), GUIUnit(height, Absolute), text_layout.left, text_layout.top,
                     text_layout.right, text_layout.bottom);
  // SDL_Log(">>> %f", layout.calculate(100, 100).w);
}

void GUIText::update(std::string new_text) {
  text = new_text;
  SDL_DestroyTexture(texture);
  texture = font->get_texture(text, color, outline_color, &width, &height);
  /* TODO: Layout update */
}

void GUIText::render(SDL_Renderer *renderer, float parent_width,
                     float parent_height) {
  SDL_FRect dst = layout.calculate(parent_width, parent_height);
  dst.x = round(dst.x);
  dst.y = round(dst.y);
  dst.w = round(dst.w);
  dst.h = round(dst.h);
  // SDL_Log("%f %f %f %f %f %f", dst.x, dst.y, dst.w, dst.h, parent_width, parent_height);
  SDL_RenderTexture(renderer, texture, NULL, &dst);
}
