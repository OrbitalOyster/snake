#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <GUI/Font.hpp>
#include <Library.hpp>
#include <SDL3/SDL.h>
#include <SDL3/SDL_pixels.h>
#include <SpriteMap.hpp>
#include <Stretchable.hpp>
#include <string>
#include <yaml-cpp/yaml.h>

struct ImageConfig {
  std::string key;
  std::string filename;
};

class Config {
private:
  /* Root YAML node */
  YAML::Node yaml;

  std::string title;
  int window_width;
  int window_height;
  SDL_Color background_color;
  bool fullscreen;
  bool resizeable;

public:
  Config(std::string filename);
  std::string get_title() const;
  int get_window_width() const;
  int get_window_height() const;
  SDL_Color get_background_color() const;
  bool get_fullscreen() const;
  bool get_resizeable() const;
  void load_images_to_library(Library *library) const;
  void load_fonts_to_library(Library *library) const;
  void load_sprite_maps_to_library(Library *library) const;
  void load_stretchables_to_library(Library *library) const;
  void load_skins_to_library(Library *library) const;
};

#endif
