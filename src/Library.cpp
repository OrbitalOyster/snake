#include "SpriteMap.hpp"
#include <Library.hpp>
#include <stdexcept>

Library::Library(SDL_Renderer *renderer) : renderer(renderer) {}

void Library::add_texture(std::string key, std::string filename) {
  if (textures.contains(key))
    throw std::runtime_error("Duplicate texture: " + key);
  textures.at(key) = new Texture(filename, renderer);
}

Texture *Library::get_texture(std::string key) {
  if (!textures.contains(key))
    throw std::runtime_error("Texture not found: " + key);
  return textures.at(key);
}

void Library::add_font(std::string key, std::string filename, float size,
                       float outline_size, SDL_Renderer *renderer) {
  if (fonts.contains(key))
    throw std::runtime_error("Duplicate font: " + key);
  fonts.at(key) = new Font(filename, size, outline_size, renderer);
}

Font *Library::get_font(std::string key) {
  if (!fonts.contains(key))
    throw std::runtime_error("Font not found: " + key);
  return fonts.at(key);
}

void Library::add_sprite_map(std::string key, float x, float y, float w,
                             float h, unsigned n, unsigned fps) {
  if (sprite_maps.contains(key))
    throw std::runtime_error("Duplicate sprite map: " + key);
  sprite_maps.at(key) = new SpriteMap(x, y, w, h, n, fps);
}

SpriteMap *Library::get_sprite_map(std::string key) {
  if (!sprite_maps.contains(key))
    throw std::runtime_error("Sprite map not found: " + key);
  return sprite_maps.at(key);
}

Library::~Library() {
  /* Destroy textures */
  for (const auto &it : textures)
    delete (textures[it.first]);
  /* Destroy fonts */
  for (const auto &it : fonts)
    delete fonts[it.first];
}
