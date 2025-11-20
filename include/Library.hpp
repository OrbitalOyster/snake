#ifndef LIBRARY_HPP_
#define LIBRARY_HPP_

#include <GUI/Font.hpp>
#include <GUI/Skin.hpp>
#include <SpriteMap.hpp>
#include <Stretchable.hpp>
#include <Texture.hpp>
#include <map>

class Library {
private:
  SDL_Renderer *renderer;
  std::map<std::string, Texture *> textures;
  std::map<std::string, Font *> fonts;
  std::map<std::string, SpriteMap *> sprite_maps;
  std::map<std::string, Stretchable *> stretchables;
  std::map<std::string, Skin *> skins;

public:
  Library(SDL_Renderer *renderer);
  void add_texture(std::string key, std::string filename);
  Texture *get_texture(std::string key);
  void add_font(std::string key, std::string filename, float size,
                float outline_size);
  Font *get_font(std::string key);
  void add_sprite_map(std::string key, float x, float y, float w, float h,
                      unsigned n, unsigned fps);
  SpriteMap *get_sprite_map(std::string key);
  void add_stretchable(std::string key, std::string texture_key,
                       SDL_FRect center, SDL_FRect top_left, SDL_FRect top,
                       SDL_FRect top_right, SDL_FRect right,
                       SDL_FRect bottom_right, SDL_FRect bottom,
                       SDL_FRect bottom_left, SDL_FRect left);
  Stretchable *get_stretchable(std::string key);
  void add_skin(std::string key, Skin *new_skin);
  Skin *get_skin(std::string key);
  ~Library();
};

#endif
