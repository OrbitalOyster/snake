#include <Stretchable.hpp>

Stretchable::Stretchable(Texture *texture, SDL_FRect center, SDL_FRect top_left,
                         SDL_FRect top, SDL_FRect top_right, SDL_FRect right,
                         SDL_FRect bottom_right, SDL_FRect bottom,
                         SDL_FRect bottom_left, SDL_FRect left)
    : texture(texture), center(center), top_left(top_left), top(top),
      top_right(top_right), right(right), bottom_right(bottom_right),
      bottom(bottom), bottom_left(bottom_left), left(left) {}

void Stretchable::render_center(SDL_FRect rect) const {
  const SDL_FRect dst = {.x = left.w,
                         .y = top.h,
                         .w = rect.w - left.w - right.w,
                         .h = rect.h - top.h - bottom.h};
  texture->render_fill(&center, &dst);
}

void Stretchable::render_top(SDL_FRect rect) const {
  const SDL_FRect dst = {
      .x = left.w, .y = 0.0, .w = rect.w - left.w - right.w, .h = top.h};
  texture->render_fill(&top, &dst);
}

void Stretchable::render_right(SDL_FRect rect) const {
  const SDL_FRect dst = {.x = rect.w - right.w,
                         .y = top.h,
                         .w = right.w,
                         .h = rect.h - top.h - bottom.h};
  texture->render_fill(&right, &dst);
}

void Stretchable::render_bottom(SDL_FRect rect) const {
  const SDL_FRect dst = {.x = left.w,
                         .y = rect.h - bottom.h,
                         .w = rect.w - left.w - right.w,
                         .h = top.h};
  texture->render_fill(&bottom, &dst);
}

void Stretchable::render_left(SDL_FRect rect) const {
  const SDL_FRect dst = {
      .x = 0.0, .y = top.h, .w = left.w, .h = rect.h - top.h - bottom.h};
  texture->render_fill(&left, &dst);
}

void Stretchable::render_top_left(SDL_FRect rect) const {
  texture->render(&top_left, rect.x, rect.y, top_left.w, top_left.h);
}

void Stretchable::render_top_right(SDL_FRect rect) const {
  texture->render(&top_right, rect.x + rect.w - top_right.w, rect.y,
                  top_right.w, top_right.h);
}

void Stretchable::render_bottom_left(SDL_FRect rect) const {
  texture->render(&bottom_left, rect.x, rect.y + rect.h - bottom_left.h,
                  bottom_left.w, bottom_left.h);
}

void Stretchable::render_bottom_right(SDL_FRect rect) const {
  texture->render(&bottom_right, rect.x + rect.w - bottom_right.w,
                  rect.y + rect.h - bottom_right.h, bottom_right.w,
                  bottom_right.h);
}

void Stretchable::render(SDL_FRect rect) const {
  render_center(rect);
  render_top(rect);
  render_right(rect);
  render_bottom(rect);
  render_left(rect);
  render_top_left(rect);
  render_top_right(rect);
  render_bottom_left(rect);
  render_bottom_right(rect);
}
