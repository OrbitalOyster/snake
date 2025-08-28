#ifndef GUI_HPP_
#define GUI_HPP_

#include <Font.hpp>
#include <Label.hpp>
#include <map>
#include <string>
#include <vector>

class GUI {
private:
  SDL_Renderer *renderer;
  std::map<std::string, Font *> fonts;
  SDL_Texture *render_text(const std::string text, TTF_Font *font,
                           SDL_Color color);
  std::vector<Label *> labels;
public:
  GUI(SDL_Renderer *renderer);
  void load_fonts(std::vector<struct FontConfig> configs);
  SDL_Texture *render_text(const std::string text, std::string font_key,
                           SDL_Color color, SDL_Color outline_color);
  void add_label(Label *label);
  void render();
};

#endif
