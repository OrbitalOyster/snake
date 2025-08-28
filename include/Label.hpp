#ifndef LABEL_HPP_
#define LABEL_HPP_

#include <SDL3_image/SDL_image.h>
#include <string>

class Label {
  private:
    std::string text;
    SDL_Texture *texture;
  public:
    Label(std::string text);
    void set_text(std::string new_text);
};

#endif
