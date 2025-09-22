#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <SDL3_image/SDL_image.h>
#include <string>

class Texture {
private:
  std::string filename;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  float w, h;

public:
  Texture(std::string filename, SDL_Renderer *renderer);
  float get_width() const;
  float get_height() const;
  void render(const SDL_FRect *dst) const;
  void render(const SDL_FRect *src, const SDL_FRect *dst) const;
  ~Texture();
};

#endif
