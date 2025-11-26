#include <Texture.hpp>
#include <cmath>
#include <stdexcept>

Texture::Texture(std::string filename, SDL_Renderer *renderer)
    : filename(filename), renderer(renderer) {
  texture = IMG_LoadTexture(renderer, filename.c_str());
  if (!texture)
    throw std::runtime_error("Failed to load image" +
                             std::string(SDL_GetError()));
  float w, h;
  SDL_GetTextureSize(texture, &w, &h);
  width = w;
  height = h;
  SDL_Log("Loaded texture %s, size %.2f x %.2f", filename.c_str(), w, h);
}

double Texture::get_width() const { return width; }

double Texture::get_height() const { return height; }

void Texture::render(const SDL_FRect *dst) const {
  SDL_RenderTexture(renderer, texture, NULL, dst);
}

// void Texture::render(const SDL_FRect *src, const SDL_FRect *dst) const {
//   SDL_RenderTexture(renderer, texture, src, dst);
// }

void Texture::render(const SDL_FRect *src, double x, double y, double w, double h) const {
  SDL_FRect dst = {(float)x, (float)y, (float)w, (float)h};
  SDL_RenderTexture(renderer, texture, src, &dst);
}

Texture::~Texture() {
  SDL_DestroyTexture(texture);
  SDL_Log("Freed texture %s", filename.c_str());
}
