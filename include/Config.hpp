#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include "SDL3/SDL_pixels.h"
#include <Font.hpp>
#include <SDL3/SDL.h>
#include <string>
#include <vector>

class Config {
private:
  std::string title;
  int window_width;
  int window_height;
  SDL_Color background_color;
  bool fullscreen;
  bool resizeable;
  std::vector<struct FontConfig> fonts;

public:
  Config(std::string filename);
  std::string get_title() const;
  int get_window_width() const;
  int get_window_height() const;
  SDL_Color get_background_color() const;
  bool get_fullscreen() const;
  bool get_resizeable() const;
  std::vector<struct FontConfig> get_fonts() const;
};

#endif
