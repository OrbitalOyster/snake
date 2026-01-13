#include "SDL3/SDL_log.h"
#include <Config.hpp>
#include <stdexcept>
#include <string>

SDL_Color hex_to_color(unsigned hex) {
  Uint8 r = hex >> 16 & 0xff;
  Uint8 g = hex >> 8 & 0xff;
  Uint8 b = hex & 0xff;
  return {r, g, b, 0xff};
}

Config::Config(std::string filename) {
  try {
    yaml = YAML::LoadFile(filename);
    /* Window section */
    YAML::Node window_yaml = yaml["window"];
    if (!window_yaml)
      throw std::runtime_error("Missing 'window' section");
    title = window_yaml["title"].as<std::string>();
    window_width = window_yaml["width"].as<int>();
    window_height = window_yaml["height"].as<int>();
    background_color =
        hex_to_color(window_yaml["background-color"].as<unsigned int>());
    fullscreen = window_yaml["fullscreen"].as<bool>();
    resizeable = window_yaml["resizeable"].as<bool>();
  } catch (const std::runtime_error err) {
    throw std::runtime_error(
        std::string("Unable to load config '" + filename + "' -> ") +
        err.what());
  }
}

std::string Config::get_title() const { return title; };
int Config::get_window_width() const { return window_width; }
int Config::get_window_height() const { return window_height; }
SDL_Color Config::get_background_color() const { return background_color; };
bool Config::get_fullscreen() const { return fullscreen; };
bool Config::get_resizeable() const { return resizeable; };

void Config::load_textures_to_library(Library *library) const {
  try {
    YAML::Node textures_yaml = yaml["textures"];
    for (YAML::const_iterator i = textures_yaml.begin();
         i != textures_yaml.end(); ++i) {
      const std::string key = i->first.as<YAML::Node>().as<std::string>();
      const auto value = i->second.as<YAML::Node>();
      const std::string filename = value["filename"].as<std::string>();
      library->add_texture(key, filename);
    }
  } catch (const std::runtime_error err) {
    throw std::runtime_error(std::string("Unable to load textures: ") +
                             err.what());
  }
}

void Config::load_fonts_to_library(Library *library) const {
  YAML::Node fonts_yaml = yaml["fonts"];
  for (YAML::const_iterator i = fonts_yaml.begin(); i != fonts_yaml.end();
       ++i) {
    const std::string key = i->first.as<YAML::Node>().as<std::string>();
    const auto value = i->second.as<YAML::Node>();
    const std::string filename = value["filename"].as<std::string>();
    const double size = value["size"].as<double>();
    /* Outline is optional */
    const double outline_size =
        value["outline_size"] ? value["outline_size"].as<double>() : 0;
    library->add_font(key, filename, size, outline_size);
  }
}

void Config::load_sprite_maps_to_library(Library *library) const {
  YAML::Node sprite_maps_yaml = yaml["sprite_maps"];
  for (YAML::const_iterator i = sprite_maps_yaml.begin();
       i != sprite_maps_yaml.end(); i++) {
    const std::string key = i->first.as<YAML::Node>().as<std::string>();
    const auto value = i->second.as<YAML::Node>();
    const int x = value["x"].as<int>();
    const int y = value["y"].as<int>();
    const int w = value["w"].as<int>();
    const int h = value["h"].as<int>();
    /* For animated sprites */
    if (value["n"].IsDefined() && value["fps"].IsDefined()) {
      const unsigned n = value["n"].as<unsigned>();
      const unsigned fps = value["fps"].as<unsigned>();
      library->add_sprite_map(key, x, y, w, h, n, fps);
    } else
      /* For static sprites */
      library->add_sprite_map(key, x, y, w, h);
  }
}

void Config::load_stretchables_to_library(Library *library) const {
  YAML::Node stretchables_yaml = yaml["stretchables"];
  for (YAML::const_iterator i = stretchables_yaml.begin();
       i != stretchables_yaml.end(); i++) {
    const std::string key = i->first.as<YAML::Node>().as<std::string>();
    const auto value = i->second.as<YAML::Node>();
    const std::string texture_key = value["texture"].as<std::string>();
    const YAML::Node center = value["center"].as<YAML::Node>();
    const YAML::Node top_left = value["top_left"].as<YAML::Node>();
    const YAML::Node top = value["top"].as<YAML::Node>();
    const YAML::Node top_right = value["top_right"].as<YAML::Node>();
    const YAML::Node right = value["right"].as<YAML::Node>();
    const YAML::Node bottom_right = value["bottom_right"].as<YAML::Node>();
    const YAML::Node bottom = value["bottom"].as<YAML::Node>();
    const YAML::Node bottom_left = value["bottom_left"].as<YAML::Node>();
    const YAML::Node left = value["left"].as<YAML::Node>();
    library->add_stretchable(
        key, texture_key,
        SDL_FRect(center["x"].as<float>(), center["y"].as<float>(),
                  center["w"].as<float>(), center["h"].as<float>()),
        SDL_FRect(top_left["x"].as<float>(), top_left["y"].as<float>(),
                  top_left["w"].as<float>(), top_left["h"].as<float>()),
        SDL_FRect(top["x"].as<float>(), top["y"].as<float>(),
                  top["w"].as<float>(), top["h"].as<float>()),
        SDL_FRect(top_right["x"].as<float>(), top_right["y"].as<float>(),
                  top_right["w"].as<float>(), top_right["h"].as<float>()),
        SDL_FRect(right["x"].as<float>(), right["y"].as<float>(),
                  right["w"].as<float>(), right["h"].as<float>()),
        SDL_FRect(bottom_right["x"].as<float>(), bottom_right["y"].as<float>(),
                  bottom_right["w"].as<float>(), bottom_right["h"].as<float>()),
        SDL_FRect(bottom["x"].as<float>(), bottom["y"].as<float>(),
                  bottom["w"].as<float>(), bottom["h"].as<float>()),
        SDL_FRect(bottom_left["x"].as<float>(), bottom_left["y"].as<float>(),
                  bottom_left["w"].as<float>(), bottom_left["h"].as<float>()),
        SDL_FRect(left["x"].as<float>(), left["y"].as<float>(),
                  left["w"].as<float>(), left["h"].as<float>()));
  }
}

void Config::load_skins_to_library(Library *library) const {
  YAML::Node skins_yaml = yaml["skins"];
  for (YAML::const_iterator i = skins_yaml.begin(); i != skins_yaml.end();
       i++) {
    const std::string key = i->first.as<YAML::Node>().as<std::string>();
    const auto value = i->second.as<YAML::Node>();
    const std::string base_key = value["base"].as<std::string>();
    const std::string hover_key =
        value["hover"].IsDefined() ? value["hover"].as<std::string>() : "";
    const std::string active_key =
        value["active"].IsDefined() ? value["active"].as<std::string>() : "";
    library->add_skin(key, base_key, hover_key, active_key);
  }
}
