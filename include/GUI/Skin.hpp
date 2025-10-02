#ifndef GUI_SKIN_HPP_
#define GUI_SKIN_HPP_

#include <SDL3/SDL_rect.h>
#include <Texture.hpp>

class GUISkin {
private:
  Texture *texture;
  SDL_FRect center;
  SDL_FRect top_left;
  SDL_FRect top;
  SDL_FRect top_right;
  SDL_FRect right;
  SDL_FRect bottom_right;
  SDL_FRect bottom;
  SDL_FRect bottom_left;
  SDL_FRect left;

  void render_center(SDL_FRect rect);
  void render_top_left(SDL_FRect rect);
  void render_top(SDL_FRect rect);
  void render_top_right(SDL_FRect rect);
  void render_right(SDL_FRect rect);
  void render_bottom_right(SDL_FRect rect);
  void render_bottom(SDL_FRect rect);
  void render_bottom_left(SDL_FRect rect);
  void render_left(SDL_FRect rect);

public:
  GUISkin(Texture *texture, SDL_FRect center, SDL_FRect top_left, SDL_FRect top,
          SDL_FRect top_right, SDL_FRect right, SDL_FRect bottom_right,
          SDL_FRect bottom, SDL_FRect bottom_left, SDL_FRect left);

  void render(SDL_FRect rect);
};

#endif
