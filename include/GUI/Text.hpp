#ifndef GUI_TEXT_HPP
#define GUI_TEXT_HPP

#include <Font.hpp>
#include <GUI/Container.hpp>
#include <string>

class GUIText {
private:
  std::string text = "";
  Font *font;
  SDL_Texture *texture;
  SDL_Color color;
  SDL_Color outline_color;
  // GUIAlignment horizontal_alignment, vertical_alignment;
  int x, y;
  /* Texture size */
  float w, h;

public:
  /*
    GUIText(std::string text, Font *font, SDL_Color color,
            SDL_Color outline_color, GUIAlignment horizontal_alignment,
            GUIAlignment vertical_alignment);
    */
  void update(std::string text);
  void render(SDL_Renderer *renderer, GUIContainer *parent);
};

#endif
