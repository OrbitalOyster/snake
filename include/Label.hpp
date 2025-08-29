#ifndef LABEL_HPP_
#define LABEL_HPP_

#include <Font.hpp>
#include <SDL3_image/SDL_image.h>
#include <string>

class Label {
private:
  std::string text;
  float x, y;
  Font *font;
  float width, height;

public:
  Label(std::string text, float x, float y, Font *font, SDL_Color color,
        SDL_Color outline_color);
  SDL_FRect get_bounding_rect() const;
  SDL_Texture *texture;
  void set_text(std::string new_text);
};

#endif
