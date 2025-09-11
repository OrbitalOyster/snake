#ifndef CORE_HPP_
#define CORE_HPP_

#include <Config.hpp>
#include <GUI.hpp>
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <Sprite.hpp>
#include <SpriteMap.hpp>
#include <map>
#include <string>
#include <vector>

class Core {
private:
  SDL_Window *window;
  std::string title;
  SDL_Color background_color;
  SDL_Renderer *renderer;
  GUI *gui;
  std::map<std::string, SDL_Texture *> textures;
  std::map<std::string, Texture *> new_textures;
  std::map<std::string, SpriteMap *> sprite_maps;
  std::vector<Sprite *> sprites;

public:
  Core(Config config);
  SDL_Renderer *get_renderer();
  void set_GUI(GUI *new_gui);
  void iterate();
  SDL_AppResult on_event(SDL_Event *event);
  SDL_Texture *load_png(std::string filename);
  Texture *get_texture(std::string texture_key);
  const SpriteMap *get_sprite_map(std::string key) const;
  void add_sprite(Sprite *sprite);
  void render_sprites();
  ~Core();
};

#endif
