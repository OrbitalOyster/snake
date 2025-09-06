#include <Sprite.hpp>

Sprite::Sprite(float x, float y, float w, float h, const SpriteMap *sprite_map)
    : x(x), y(y), w(w), h(h), sprite_map(sprite_map) {}

void Sprite::render() {}
