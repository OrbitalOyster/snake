#ifndef LABEL_HPP_
#define LABEL_HPP_

#include <SDL3_image/SDL_image.h>
#include <string>

class Label {
private:
public:
  Label(std::string text, float x, float y);
  std::string text;
  SDL_Texture *texture;
  float x, y;
  void set_text(std::string new_text);
};

#endif
