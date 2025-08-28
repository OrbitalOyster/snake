#ifndef CORE_HPP_
#define CORE_HPP_

#include <Config.hpp>
#include <GUI.hpp>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

class Core {
private:
  SDL_Window *window;
  std::string title;
  SDL_Color background_color;
  GUI *gui;

public:
  Core(Config config);
  void set_GUI(GUI *new_gui);
  void iterate();
  SDL_AppResult on_event(SDL_Event *event);
  SDL_Texture *load_png(const char *filename);
  SDL_Texture *hello;
  SDL_Renderer *renderer;
  ~Core();
};

#endif
