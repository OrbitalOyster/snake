#include "SDL3/SDL_log.h"
#include <Texture.hpp>
#include <Utils.hpp>
#include <cmath>
#include <stdexcept>

Texture::Texture(std::string filename, SDL_Renderer *renderer)
    : filename(filename), renderer(renderer) {
  texture = IMG_LoadTexture(renderer, filename.c_str());
  if (!texture)
    throw std::runtime_error("Failed to load image" +
                             std::string(SDL_GetError()));
  SDL_GetTextureSize(texture, &width, &height);
  SDL_Log("Loaded texture %s, size %f x %f", filename.c_str(), width, height);
}

float Texture::get_width() const { return width; }

float Texture::get_height() const { return height; }

void Texture::render(const SDL_FRect *dst) const {
  SDL_RenderTexture(renderer, texture, NULL, dst);
}

void Texture::render(const SDL_FRect *src, double x, double y, double w,
                     double h) const {
  SDL_FRect dst = get_frect(x, y, w, h);
  SDL_RenderTexture(renderer, texture, src, &dst);
}

void Texture::render(const SDL_FRect src, double x, double y, double w,
                     double h) const {
  SDL_FRect dst = get_frect(x, y, w, h);
  SDL_RenderTexture(renderer, texture, &src, &dst);
}

void Texture::render_fill(const SDL_FRect *src, const SDL_FRect *dst) const {
  /* Some edge cases */
  if (src->w <= 0 || src->h <= 0 || dst->w <= 0 || dst->h <= 0)
    return;
  const SDL_FRect src_r = get_frect(*src);
  const SDL_FRect dst_r = get_frect(*dst);
  const unsigned rows = dst_r.h / src_r.h;
  const unsigned cols = dst_r.w / src_r.w;
  /* Remainders */
  const float x_partial = fmod(dst_r.w, src_r.w);
  const float y_partial = fmod(dst_r.h, src_r.h);
  for (unsigned row = 0; row < rows; row++) {
    for (unsigned col = 0; col < cols; col++) {
      SDL_FRect dst_tile = {dst_r.x + src_r.w * col, dst_r.y + src_r.h * row,
                            src_r.w, src_r.h};
      SDL_RenderTexture(renderer, texture, &src_r, &dst_tile);
    }
    /* Row remainder */
    SDL_FRect src_tile = {src_r.x, src_r.y, x_partial, src_r.h};
    SDL_FRect dst_tile = {dst_r.x + src_r.w * cols, dst_r.y + src_r.h * row,
                          x_partial, src_r.h};
    SDL_RenderTexture(renderer, texture, &src_tile, &dst_tile);
  }
  /* Col remainder */
  for (unsigned col = 0; col < cols; col++) {
    SDL_FRect src_tile = {src_r.x, src_r.y, src_r.w, y_partial};
    SDL_FRect dst_tile = {dst_r.x + src_r.w * col, dst_r.y + src_r.h * rows,
                          src_r.w, y_partial};
    SDL_RenderTexture(renderer, texture, &src_tile, &dst_tile);
  }
  /* Bottom-right corner */
  SDL_FRect src_tile = {src_r.x, src_r.y, x_partial, y_partial};
  SDL_FRect dst_tile = {dst_r.x + src_r.w * cols, dst_r.y + src_r.h * rows,
                        x_partial, y_partial};
  SDL_RenderTexture(renderer, texture, &src_tile, &dst_tile);
}

Texture::~Texture() {
  SDL_DestroyTexture(texture);
  SDL_Log("Freed texture %s", filename.c_str());
}
