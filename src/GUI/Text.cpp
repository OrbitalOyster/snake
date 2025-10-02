#include <GUI/Text.hpp>

GUIText::GUIText(std::string text, Font *font, SDL_Color color,
                 SDL_Color outline_color, TextLayout layout)
    : text(text), font(font), color(color), outline_color(outline_color) {
  texture = font->get_texture(text, color, outline_color, &w, &h);
  container = GUIContainer({.width = (unsigned)w,
                            .height = (unsigned)h,
                            .top = layout.top,
                            .left = layout.left,
                            .bottom = layout.bottom,
                            .right = layout.right});
}

void GUIText::update(std::string text) {
  this->text = text;
  SDL_DestroyTexture(texture);
  texture = font->get_texture(text, color, outline_color, &w, &h);
}

void GUIText::render(SDL_Renderer *renderer, GUIContainer *parent) {
  container.update(parent->get_width(), parent->get_height());
  SDL_FRect dst = container.get_bounding_rect();
  SDL_RenderTexture(renderer, texture, NULL, &dst);
  container.render(renderer, parent->get_x(), parent->get_y());
}
