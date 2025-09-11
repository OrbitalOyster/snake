#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <SDL3_image/SDL_image.h>
#include <string>

class Texture {
private:
  SDL_Texture *texture;

public:
  Texture(std::string filename, SDL_Renderer *renderer);
  void render(SDL_Renderer *renderer, SDL_FRect *src, SDL_FRect *dst);
  ~Texture();
};

#endif
