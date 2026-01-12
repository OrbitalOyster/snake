#include <SDL3/SDL_log.h>
#include <Texture.hpp>
#include <cmath>
#include <stdexcept>

Texture::Texture(std::string filename, SDL_Renderer *renderer)
    : filename(filename), renderer(renderer) {
  texture = IMG_LoadTexture(renderer, filename.c_str());
  if (!texture)
    throw std::runtime_error("Failed to load image" +
                             std::string(SDL_GetError()));
  SDL_GetTextureSize(texture, &width, &height);
  SDL_Log("Loaded texture %s, size %.2f x %.2f", filename.c_str(), width,
          height);
}

double Texture::get_width() const { return width; }

double Texture::get_height() const { return height; }

void Texture::render(const SDL_FRect *dst) const {
  SDL_RenderTexture(renderer, texture, NULL, dst);
}

void Texture::render(const SDL_FRect *src, double x, double y, double w,
                     double h) const {
  SDL_FRect dst = {(float)x, (float)y, (float)w, (float)h};
  SDL_RenderTexture(renderer, texture, src, &dst);
}

void Texture::render(const SDL_FRect src, double x, double y, double w,
                     double h) const {
  SDL_FRect dst = {(float)x, (float)y, (float)w, (float)h};
  SDL_RenderTexture(renderer, texture, &src, &dst);
}

void Texture::render_fill(const SDL_FRect *src, const SDL_FRect *dst) const {
  const unsigned rows = dst->h / src->h;
  const unsigned cols = dst->w / src->w;
  if (!rows || !cols)
    return;
  /* Remainders */
  const double x_partial = fmod(dst->w, src->w);
  const double y_partial = fmod(dst->h, src->h);
  for (unsigned row = 0; row < rows; row++) {
    for (unsigned col = 0; col < cols; col++) {
      SDL_FRect dst_tile = {(float)(dst->x + src->w * col),
                            (float)(dst->y + src->h * row), (float)src->w,
                            (float)src->h};
      SDL_RenderTexture(renderer, texture, src, &dst_tile);
    }
    /* Row remainder */
    SDL_FRect src_tile = {(float)(src->x), (float)(src->y), (float)x_partial,
                          (float)src->h};
    SDL_FRect dst_tile = {(float)(dst->x + src->w * cols),
                          (float)(dst->y + src->h * row), (float)x_partial,
                          (float)src->h};
    SDL_RenderTexture(renderer, texture, &src_tile, &dst_tile);
  }
  /* Col remainder */
  for (unsigned col = 0; col < cols; col++) {
    SDL_FRect src_tile = {(float)(src->x), (float)(src->y), (float)src->w,
                          (float)y_partial};
    SDL_FRect dst_tile = {(float)(dst->x + src->w * col),
                          (float)(dst->y + src->h * rows), (float)src->w,
                          (float)y_partial};
    SDL_RenderTexture(renderer, texture, &src_tile, &dst_tile);
  }
  /* Bottom-right corner */
  SDL_FRect src_tile = {(float)(src->x), (float)(src->y), (float)x_partial,
                        (float)y_partial};
  SDL_FRect dst_tile = {(float)(dst->x + src->w * cols),
                        (float)(dst->y + src->h * rows), (float)x_partial,
                        (float)y_partial};
  SDL_RenderTexture(renderer, texture, &src_tile, &dst_tile);
}

Texture::~Texture() {
  SDL_DestroyTexture(texture);
  SDL_Log("Freed texture %s", filename.c_str());
}
