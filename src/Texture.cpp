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

  const SDL_FRect _src = {.x = (float)round(src->x),
                          .y = (float)round(src->y),
                          .w = (float)round(src->w),
                          .h = (float)round(src->h)};
  const SDL_FRect _dst = {.x = (float)round(dst->x),
                          .y = (float)round(dst->y),
                          .w = (float)round(dst->w),
                          .h = (float)round(dst->h)};

  const unsigned rows = _dst.h / _src.h;
  const unsigned cols = _dst.w / _src.w;
  if (!rows || !cols)
    return;
  /* Remainders */
  const double x_partial = fmod(_dst.w, _src.w);
  const double y_partial = fmod(_dst.h, _src.h);
  for (unsigned row = 0; row < rows; row++) {
    for (unsigned col = 0; col < cols; col++) {
      SDL_FRect dst_tile = {(float)(_dst.x + _src.w * col),
                            (float)(_dst.y + _src.h * row), (float)_src.w,
                            (float)_src.h};
      SDL_RenderTexture(renderer, texture, &_src, &dst_tile);
    }
    /* Row remainder */
    SDL_FRect src_tile = {(float)(_src.x), (float)(_src.y), (float)x_partial,
                          (float)_src.h};
    SDL_FRect dst_tile = {(float)(_dst.x + _src.w * cols),
                          (float)(_dst.y + _src.h * row), (float)x_partial,
                          (float)_src.h};
    SDL_RenderTexture(renderer, texture, &src_tile, &dst_tile);
  }
  /* Col remainder */
  for (unsigned col = 0; col < cols; col++) {
    SDL_FRect src_tile = {(float)(_src.x), (float)(_src.y), (float)_src.w,
                          (float)y_partial};
    SDL_FRect dst_tile = {(float)(_dst.x + _src.w * col),
                          (float)(_dst.y + _src.h * rows), (float)_src.w,
                          (float)y_partial};
    SDL_RenderTexture(renderer, texture, &src_tile, &dst_tile);
  }
  /* Bottom-right corner */
  SDL_FRect src_tile = {(float)(_src.x), (float)(_src.y), (float)x_partial,
                        (float)y_partial};
  SDL_FRect dst_tile = {(float)(_dst.x + _src.w * cols),
                        (float)(_dst.y + _src.h * rows), (float)x_partial,
                        (float)y_partial};
  SDL_RenderTexture(renderer, texture, &src_tile, &dst_tile);
}

Texture::~Texture() {
  SDL_DestroyTexture(texture);
  SDL_Log("Freed texture %s", filename.c_str());
}
