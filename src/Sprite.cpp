#include <Sprite.hpp>

// Sprite::Sprite(float x, float y, float w, float h, const SpriteMap
// *sprite_map)
//     : x(x), y(y), w(w), h(h), sprite_map(sprite_map) {}

Sprite::Sprite(float x, float y, float w, float h, Texture *texture)
    : x(x), y(y), w(w), h(h), texture(texture) {}

Sprite::Sprite(float x, float y, float w, float h, Texture *texture,
               const SpriteMap *sprite_map)
    : x(x), y(y), w(w), h(h), texture(texture), sprite_map(sprite_map) {}

/*
void Sprite::render(unsigned long ticks, SDL_Renderer *renderer) const {
  const SDL_FRect dst = {x, y, w, h};
  if (sprite_map) {
    SDL_FRect src = sprite_map->get_frame(animation_start_time, ticks);
    SDL_RenderTexture(renderer, sprite_map->get_texture(), &src, &dst);
  }
}
*/

void Sprite::render(unsigned long ticks) const {
  const SDL_FRect dst = {x, y, w, h};
  if (sprite_map) {
    SDL_FRect src = sprite_map->get_frame(animation_start_time, ticks);
    texture->render(&src, &dst);
  }
}
