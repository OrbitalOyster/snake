#include "SDL3/SDL_rect.h"
#include <Texture.hpp>
#include <cmath>
#include <stdexcept>

Texture::Texture(std::string filename, SDL_Renderer *renderer)
    : filename(filename), renderer(renderer) {
  texture = IMG_LoadTexture(renderer, filename.c_str());
  if (!texture)
    throw std::runtime_error("Failed to load image" +
                             std::string(SDL_GetError()));
  SDL_GetTextureSize(texture, &w, &h);
  SDL_Log("Loaded texture %s, size %.2f x %.2f", filename.c_str(), w, h);
}

float Texture::get_width() const { return w; }

float Texture::get_height() const { return h; }

void Texture::render(const SDL_FRect *dst) const {
  SDL_RenderTexture(renderer, texture, NULL, dst);
}

void Texture::render(const SDL_FRect *src, const SDL_FRect *dst) const {
  SDL_RenderTexture(renderer, texture, src, dst);
}

Texture::~Texture() {
  SDL_DestroyTexture(texture);
  SDL_Log("Freed texture %s", filename.c_str());
}
