#include <Sprite.hpp>

Sprite::Sprite(double x, double y, double w, double h, Texture *texture)
    : x(x), y(y), w(w), h(h), texture(texture) {}

Sprite::Sprite(double x, double y, double w, double h, Texture *texture,
               const SpriteMap *sprite_map)
    : x(x), y(y), w(w), h(h), texture(texture), sprite_map(sprite_map) {}

void Sprite::render(unsigned long ticks) const {
  if (sprite_map) {
    SDL_FRect src = sprite_map->get_frame(animation_start_time, ticks);
    texture->render(&src, x, y, w, h);
  } else {
    SDL_FRect src = {0.0, 0.0, (float)texture->get_width(),
                     (float)texture->get_height()};
    texture->render(&src, x, y, w, h);
  }
}
