#ifndef GUI_TEXT_HPP
#define GUI_TEXT_HPP

#include <GUI/Segment.hpp>
#include <GUI/Font.hpp>
#include <optional>
#include <string>

struct TextLayout {
  std::optional<GUISegment> top, left;
  std::optional<GUISegment> bottom, right;
};

class GUIText {
private:
  std::string text = "";
  Font *font;
  SDL_Texture *texture;
  SDL_Color color;
  SDL_Color outline_color;
  std::optional<GUISegment> top = {}, left = {};
  std::optional<GUISegment> bottom = {}, right = {};
  float w, h;

public:
  GUIText(std::string text, Font *font, SDL_Color color,
          SDL_Color outline_color, TextLayout layout);
  void update(std::string text);
  void render(SDL_Renderer *renderer, float parent_width, float parent_height);
};

#endif
