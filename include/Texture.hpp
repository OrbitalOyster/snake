#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <SDL3_image/SDL_image.h>
#include <string>

class Texture {
private:
  std::string filename;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  double width, height;

public:
  Texture(std::string filename, SDL_Renderer *renderer);
  double get_width() const;
  double get_height() const;
  void render(const SDL_FRect *dst) const;
//  void render(const SDL_FRect *src, const SDL_FRect *dst) const;
  void render(const SDL_FRect *src, double x, double y, double w, double h) const;
  ~Texture();
};

#endif
