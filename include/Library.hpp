#ifndef LIBRARY_HPP_
#define LIBRARY_HPP_

#include <Font.hpp>
#include <SpriteMap.hpp>
#include <Texture.hpp>
#include <map>

class Library {
private:
  SDL_Renderer *renderer;
  std::map<std::string, Texture *> textures;
  std::map<std::string, Font *> fonts;
  std::map<std::string, SpriteMap *> sprite_maps;

public:
  Library(SDL_Renderer *renderer);
  void add_texture(std::string key, std::string filename);
  Texture *get_texture(std::string key);
  void add_font(std::string key, std::string filename, float size,
                float outline_size, SDL_Renderer *renderer);
  Font *get_font(std::string key);
  void add_sprite_map(std::string key, float x, float y, float w, float h,
                      unsigned n, unsigned fps);
  SpriteMap *get_sprite_map(std::string key);
  ~Library();
};

#endif
