#include <Sprite.hpp>

Sprite::Sprite(double x, double y, double w, double h, Texture *texture,
               const SpriteMap *sprite_map)
    : x(x), y(y), w(w), h(h), texture(texture), sprite_map(sprite_map) {}

/* Static sprites */
void Sprite::render() const {
  SDL_FRect src;
  if (sprite_map)
    src = sprite_map->get_frame(animation_start_time, 0);
  else
    src = {0.0, 0.0, (float)texture->get_width(), (float)texture->get_height()};
  texture->render(&src, x, y, w, h);
}

/* Animated sprites */
void Sprite::render(unsigned long ticks) const {
  SDL_FRect src;
  if (sprite_map)
    src = sprite_map->get_frame(animation_start_time, ticks);
  else
    src = {0.0, 0.0, (float)texture->get_width(), (float)texture->get_height()};
  texture->render(&src, x, y, w, h);
}
