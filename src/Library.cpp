#include <Library.hpp>
#include <optional>
#include <stdexcept>

Library::Library(SDL_Renderer *renderer) : renderer(renderer) {}

void Library::add_texture(std::string key, std::string filename) {
  if (textures.contains(key))
    throw std::runtime_error("Duplicate texture: " + key);
  textures[key] = new Texture(filename, renderer);
}

Texture *Library::get_texture(std::string key) {
  if (!textures.contains(key))
    throw std::runtime_error("Texture not found: " + key);
  return textures.at(key);
}

void Library::add_font(std::string key, std::string filename, double size,
                       double outline_size) {
  if (fonts.contains(key))
    throw std::runtime_error("Duplicate font: " + key);
  fonts[key] = new Font(filename, size, outline_size, renderer);
}

Font *Library::get_font(std::string key) {
  if (!fonts.contains(key))
    throw std::runtime_error("Font not found: " + key);
  return fonts.at(key);
}

void Library::add_sprite_map(std::string key, double x, double y, double w,
                             double h, unsigned n, unsigned fps) {
  if (sprite_maps.contains(key))
    throw std::runtime_error("Duplicate sprite map: " + key);
  sprite_maps[key] = new SpriteMap(x, y, w, h, n, fps);
}

SpriteMap *Library::get_sprite_map(std::string key) {
  if (!sprite_maps.contains(key))
    throw std::runtime_error("Sprite map not found: " + key);
  return sprite_maps.at(key);
}

void Library::add_stretchable(std::string key, std::string texture_key,
                              SDL_FRect center, SDL_FRect top_left,
                              SDL_FRect top, SDL_FRect top_right,
                              SDL_FRect right, SDL_FRect bottom_right,
                              SDL_FRect bottom, SDL_FRect bottom_left,
                              SDL_FRect left) {
  if (stretchables.contains(key))
    throw std::runtime_error("Duplicate stretchable: " + key);
  Texture *texture = get_texture(texture_key);
  stretchables[key] =
      new Stretchable(texture, center, top_left, top, top_right, right,
                      bottom_right, bottom, bottom_left, left);
}

Stretchable *Library::get_stretchable(std::string key) {
  if (!stretchables.contains(key))
    throw std::runtime_error("Stretchable not found: " + key);
  return stretchables.at(key);
}

void Library::add_skin(std::string key, std::string base_key,
                       std::optional<std::string> hover_key,
                       std::optional<std::string> active_key) {
  if (skins.contains(key))
    throw std::runtime_error("Duplicate skin: " + key);
  Stretchable *base = stretchables[base_key];
  std::optional<Stretchable *> hover;
  std::optional<Stretchable *> active;
  if (hover_key.has_value())
    hover = stretchables[hover_key.value()];
  if (active_key.has_value())
    active = stretchables[active_key.value()];
  skins[key] = new Skin(base, hover, active);
}

Skin *Library::get_skin(std::string key) {
  if (!skins.contains(key))
    throw std::runtime_error("Skin not found: " + key);
  return skins[key];
}

Library::~Library() {
  /* Destroy textures */
  for (const auto &it : textures)
    delete (textures[it.first]);
  /* Destroy fonts */
  for (const auto &it : fonts)
    delete fonts[it.first];
}
