#ifndef GUI_TEXT_HPP_
#define GUI_TEXT_HPP_

#include <GUI/Font.hpp>
#include <GUI/Layout.hpp>
#include <GUI/Segment.hpp>
#include <optional>
#include <string>

struct TextLayout {
  std::optional<GUISegment> left;
  std::optional<GUISegment> top;
  std::optional<GUISegment> right;
  std::optional<GUISegment> bottom;
};

class GUIText {
private:
  std::string text = "";
  Font *font;
  SDL_Texture *texture;
  SDL_Color color, outline_color;
  GUILayout layout;
  /* Texture size */
  double width, height;

public:
  GUIText(std::string text, Font *font, SDL_Color color,
          SDL_Color outline_color, TextLayout layout);
  void update(std::string text);
  void render(SDL_Renderer *renderer, double parent_width, double parent_height);
};

#endif
