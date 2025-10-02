#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <Font.hpp>
#include <GUI/Skin.hpp>
#include <Library.hpp>
#include <SDL3/SDL.h>
#include <SDL3/SDL_pixels.h>
#include <SpriteMap.hpp>
#include <string>
#include <vector>
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
  std::vector<struct FontConfig> font_configs;
  std::vector<struct ImageConfig> image_configs;
  std::vector<struct SpriteMapConfig> sprite_map_configs;
  std::vector<struct SkinConfig> skin_configs;

public:
  Config(std::string filename);
  void load_images_to_library(Library *library) const;
  void load_fonts_to_library(Library *library, SDL_Renderer *renderer) const;
  void load_sprite_maps_to_library(Library *library) const;
  std::string get_title() const;
  int get_window_width() const;
  int get_window_height() const;
  SDL_Color get_background_color() const;
  bool get_fullscreen() const;
  bool get_resizeable() const;
  std::vector<FontConfig> get_fonts() const;
  std::vector<ImageConfig> get_images() const;
  std::vector<SpriteMapConfig> get_sprite_maps() const;
  std::vector<SkinConfig> get_skin_configs() const;
};

#endif
