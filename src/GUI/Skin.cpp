#include <GUI/Skin.hpp>

GUISkin::GUISkin(Texture *texture, SDL_FRect center, SDL_FRect top_left,
                 SDL_FRect top, SDL_FRect top_right, SDL_FRect right,
                 SDL_FRect bottom_right, SDL_FRect bottom,
                 SDL_FRect bottom_left, SDL_FRect left)
    : texture(texture), center(center), top_left(top_left), top(top),
      top_right(top_right), right(right), bottom_right(bottom_right),
      bottom(bottom), bottom_left(bottom_left), left(left) {}

void GUISkin::render_center(SDL_FRect rect) {
  for (unsigned y = top.h; y < rect.h - bottom.h; y += center.h)
    for (unsigned x = left.w; x < rect.w - right.w; x += center.w) {
      SDL_FRect dst = {rect.x + x, rect.y + y, center.w, center.h};
      texture->render(&center, &dst);
    }
}

void GUISkin::render_top_left(SDL_FRect rect) {
  SDL_FRect dst = {rect.x, rect.y, top_left.w, top_left.h};
  texture->render(&top_left, &dst);
}

void GUISkin::render_top(SDL_FRect rect) {
  for (unsigned i = top_left.w; i < rect.w - top_right.w; i += top.w) {
    SDL_FRect dst = {rect.x + i, rect.y, top.w, top.h};
    texture->render(&top, &dst);
  }
}

void GUISkin::render_top_right(SDL_FRect rect) {
  SDL_FRect dst = {rect.x + rect.w - top_right.w, rect.y, top_right.w,
                   top_right.h};
  texture->render(&top_right, &dst);
}

void GUISkin::render_right(SDL_FRect rect) {
  for (unsigned i = top_right.h; i < rect.h - bottom_right.w; i += right.h) {
    SDL_FRect dst = {rect.x + rect.w - right.w, rect.y + i, right.w, right.h};
    texture->render(&right, &dst);
  }
}

void GUISkin::render_bottom_right(SDL_FRect rect) {
  SDL_FRect dst = {rect.x + rect.w - bottom_right.w,
                   rect.y + rect.h - bottom_right.h, bottom_right.w,
                   bottom_right.h};
  texture->render(&bottom_right, &dst);
}

void GUISkin::render_bottom(SDL_FRect rect) {
  for (unsigned i = bottom_left.w; i < rect.w - bottom_right.w; i += bottom.w) {
    SDL_FRect dst = {rect.x + i, rect.y + rect.h - bottom.h, bottom.w,
                     bottom.h};
    texture->render(&bottom, &dst);
  }
}

void GUISkin::render_left(SDL_FRect rect) {
  for (unsigned i = top_left.h; i < rect.h - bottom_left.w; i += left.h) {
    SDL_FRect dst = {rect.x, rect.y + i, left.w, left.h};
    texture->render(&left, &dst);
  }
}

void GUISkin::render_bottom_left(SDL_FRect rect) {
  SDL_FRect dst = {rect.x, rect.y + rect.h - bottom_left.h, bottom_left.w,
                   bottom_left.h};
  texture->render(&bottom_left, &dst);
}

void GUISkin::render(SDL_FRect rect) {
  render_center(rect);
  render_top(rect);
  render_right(rect);
  render_bottom(rect);
  render_left(rect);
  render_top_right(rect);
  render_bottom_right(rect);
  render_bottom_left(rect);
  render_top_left(rect);
}
