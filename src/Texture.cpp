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
  float w, h;
  SDL_GetTextureSize(texture, &w, &h);
  width = round(w);
  height = round(h);
  SDL_Log("Loaded texture %s, size %u x %u", filename.c_str(), width, height);
}

unsigned Texture::get_width() const { return width; }

unsigned Texture::get_height() const { return height; }

void Texture::render(const SDL_FRect *dst) const {
  SDL_RenderTexture(renderer, texture, NULL, dst);
}

void Texture::render(const SDL_FRect *src, double x, double y, double w,
                     double h) const {
  SDL_FRect dst = {(float)round(x), (float)round(y), (float)round(w),
                   (float)round(h)};
  SDL_RenderTexture(renderer, texture, src, &dst);
}

void Texture::render(const SDL_FRect src, double x, double y, double w,
                     double h) const {
  SDL_FRect dst = {(float)round(x), (float)round(y), (float)round(w),
                   (float)round(h)};
  SDL_RenderTexture(renderer, texture, &src, &dst);
}

void Texture::render_fill(const SDL_FRect *src, const SDL_FRect *dst) const {
  const SDL_FRect rounded_src = {.x = (float)round(src->x),
                                 .y = (float)round(src->y),
                                 .w = (float)round(src->w),
                                 .h = (float)round(src->h)};
  const SDL_FRect rounded_dst = {.x = (float)round(dst->x),
                                 .y = (float)round(dst->y),
                                 .w = (float)round(dst->w),
                                 .h = (float)round(dst->h)};
  const float rows = rounded_dst.h / rounded_src.h;
  const float cols = rounded_dst.w / rounded_src.w;
  if (!rows || !cols)
    return;
  /* Remainders */
  const float x_partial = fmod(rounded_dst.w, rounded_src.w);
  const float y_partial = fmod(rounded_dst.h, rounded_src.h);
  for (unsigned row = 0; row < rows; row++) {
    for (unsigned col = 0; col < cols; col++) {
      SDL_FRect dst_tile = {rounded_dst.x + rounded_src.w * col,
                            (rounded_dst.y + rounded_src.h * row),
                            rounded_src.w, rounded_src.h};
      SDL_RenderTexture(renderer, texture, &rounded_src, &dst_tile);
    }
    /* Row remainder */
    SDL_FRect src_tile = {rounded_src.x, (rounded_src.y), x_partial,
                          rounded_src.h};
    SDL_FRect dst_tile = {rounded_dst.x + rounded_src.w * cols,
                          rounded_dst.y + rounded_src.h * row, x_partial,
                          rounded_src.h};
    SDL_RenderTexture(renderer, texture, &src_tile, &dst_tile);
  }
  /* Col remainder */
  for (unsigned col = 0; col < cols; col++) {
    SDL_FRect src_tile = {rounded_src.x, rounded_src.y, rounded_src.w,
                          y_partial};
    SDL_FRect dst_tile = {rounded_dst.x + rounded_src.w * col,
                          rounded_dst.y + rounded_src.h * rows, rounded_src.w,
                          y_partial};
    SDL_RenderTexture(renderer, texture, &src_tile, &dst_tile);
  }
  /* Bottom-right corner */
  SDL_FRect src_tile = {rounded_src.x, rounded_src.y, x_partial, y_partial};
  SDL_FRect dst_tile = {(rounded_dst.x + rounded_src.w * cols),
                        (rounded_dst.y + rounded_src.h * rows), x_partial,
                        y_partial};
  SDL_RenderTexture(renderer, texture, &src_tile, &dst_tile);
}

Texture::~Texture() {
  SDL_DestroyTexture(texture);
  SDL_Log("Freed texture %s", filename.c_str());
}
