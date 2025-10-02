#include <GUI/Text.hpp>
#include <GUI/Container.hpp>

GUIText::GUIText(std::string text, Font *font, SDL_Color color,
                 SDL_Color outline_color, TextLayout layout)
    : text(text), font(font), color(color), outline_color(outline_color) {
  texture = font->get_texture(text, color, outline_color, &w, &h);
  if (layout.top.has_value())
    top = layout.top.value();
  if (layout.left.has_value())
    left = layout.left.value();
  if (layout.bottom.has_value())
    bottom = layout.bottom.value();
  if (layout.right.has_value())
    right = layout.right.value();
}

void GUIText::update(std::string text) {
  this->text = text;
  SDL_DestroyTexture(texture);
  texture = font->get_texture(text, color, outline_color, &w, &h);
}

void GUIText::render(SDL_Renderer *renderer, float parent_width, float parent_height) {
  GUIContainer container = GUIContainer({.width = (unsigned)w,
                            .height = (unsigned)h,
                            .top = top,
                            .left = left,
                            .bottom = bottom,
                            .right = right});
  container.update(parent_width, parent_height);
  SDL_FRect dst = container.get_bounding_rect();
  SDL_RenderTexture(renderer, texture, NULL, &dst);
  // container.render(renderer, parent->get_x(), parent->get_y());
}
