#include <Texture.hpp>
#include <stdexcept>

Texture::Texture(std::string filename, SDL_Renderer *renderer)
    : filename(filename), renderer(renderer) {
  texture = IMG_LoadTexture(renderer, filename.c_str());
  if (!texture)
    throw std::runtime_error("Failed to load image" +
                             std::string(SDL_GetError()));
  SDL_Log("Loaded texture %s", filename.c_str());
}

void Texture::render(const SDL_FRect *src, const SDL_FRect *dst) const {
  SDL_RenderTexture(renderer, texture, src, dst);
}

Texture::~Texture() {
  SDL_DestroyTexture(texture);
  SDL_Log("Freed texture %s", filename.c_str());
}
