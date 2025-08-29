#ifndef CORE_HPP_
#define CORE_HPP_

#include "Sprite.hpp"
#include <Config.hpp>
#include <GUI.hpp>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <vector>

class Core {
private:
  SDL_Window *window;
  std::string title;
  SDL_Color background_color;
  SDL_Renderer *renderer;
  GUI *gui;
  unsigned int ticks = 0;

  std::vector<Sprite> sprites;

public:
  Core(Config config);
  SDL_Renderer *get_renderer();
  void set_GUI(GUI *new_gui);
  void iterate();
  unsigned int get_ticks();
  SDL_AppResult on_event(SDL_Event *event);
  SDL_Texture *load_png(std::string filename);
  void render_sprites();
  // SDL_Texture *hello;
  ~Core();
};

#endif
