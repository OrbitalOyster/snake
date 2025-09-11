#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <SDL3_image/SDL_image.h>
#include <string>

class Texture {
private:
  std::string filename;
  SDL_Renderer *renderer;
  SDL_Texture *texture;

public:
  Texture(std::string filename, SDL_Renderer *renderer);
  void render(const SDL_FRect *src, const SDL_FRect *dst) const;
  ~Texture();
};

#endif
