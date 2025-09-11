#include "SDL3_image/SDL_image.h"
#include <Texture.hpp>
#include <stdexcept>

Texture::Texture(std::string filename, SDL_Renderer *renderer) {
  texture = IMG_LoadTexture(renderer, filename.c_str());
  if (!texture)
    throw std::runtime_error("Failed to load image" +
                             std::string(SDL_GetError()));
  SDL_Log("Loaded texture %s", filename.c_str());
}

void Texture::render(SDL_Renderer *renderer, SDL_FRect *src, SDL_FRect *dst) {
  SDL_RenderTexture(renderer, texture, src, dst);
}

Texture::~Texture() { SDL_DestroyTexture(texture); }
