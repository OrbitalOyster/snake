#include <Sprite.hpp>

Sprite::Sprite(SpriteMap *sprite_map, float x, float y, float w, float h)
    : sprite_map(sprite_map), x(x), y(y), w(w), h(h) {}

void Sprite::render() {}
