#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <SDL3/SDL_rect.h>
#include <cmath>

inline SDL_FRect get_frect(SDL_FRect r) {
  return {.x = (float)round(r.x),
          .y = (float)round(r.y),
          .w = (float)round(r.w),
          .h = (float)round(r.h)};
}

inline SDL_FRect get_frect(double x, double y, double w, double h) {
  return {.x = (float)round(x),
          .y = (float)round(y),
          .w = (float)round(w),
          .h = (float)round(h)};
}
#endif
