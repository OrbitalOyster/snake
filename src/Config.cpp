#include <Config.hpp>
#include <stdexcept>
#include <yaml-cpp/yaml.h>

SDL_Color hex_to_color(unsigned hex) {
  Uint8 r = hex >> 16 & 0xff;
  Uint8 g = hex >> 8 & 0xff;
  Uint8 b = hex & 0xff;
  return {r, g, b, 0xff};
}

Config::Config(std::string filename) {
  try {
    YAML::Node yaml = YAML::LoadFile(filename);
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
    /* Fonts section */
    YAML::Node fonts_yaml = yaml["fonts"];
    for (YAML::const_iterator f = fonts_yaml.begin(); f != fonts_yaml.end();
         ++f) {
      const std::string key = f->first.as<YAML::Node>().as<std::string>();
      const auto value = f->second.as<YAML::Node>();
      const std::string filename = value["filename"].as<std::string>();
      const float size = value["size"].as<float>();
      /* Outline is optional */
      const float outline = value["outline"] ? value["outline"].as<float>() : 0;
      font_configs.push_back({key, filename, size, outline});
    }
    /* Images */
    YAML::Node images_yaml = yaml["images"];
    for (YAML::const_iterator i = images_yaml.begin(); i != images_yaml.end();
         ++i) {
      const std::string key = i->first.as<YAML::Node>().as<std::string>();
      const auto value = i->second.as<YAML::Node>();
      const std::string filename = value["filename"].as<std::string>();
      image_configs.push_back({key, filename});
    }
    /* Sprite maps */
    YAML::Node sprite_maps_yaml = yaml["sprite_maps"];
    for (YAML::const_iterator m = sprite_maps_yaml.begin();
         m != sprite_maps_yaml.end(); m++) {
      const std::string key = m->first.as<YAML::Node>().as<std::string>();
      const auto value = m->second.as<YAML::Node>();
      const std::string texture = value["texture"].as<std::string>();
      const unsigned x = value["x"].as<unsigned>();
      const unsigned y = value["y"].as<unsigned>();
      const unsigned w = value["w"].as<unsigned>();
      const unsigned h = value["h"].as<unsigned>();
      const unsigned n = value["n"].as<unsigned>();
      const unsigned fps = value["fps"].as<unsigned>();
      sprite_map_configs.push_back({key, texture, x, y, w, h, n, fps});
    }

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
std::vector<struct FontConfig> Config::get_fonts() const {
  return font_configs;
};
std::vector<struct ImageConfig> Config::get_images() const {
  return image_configs;
};
std::vector<struct SpriteMapConfig> Config::get_sprite_maps() const {
  return sprite_map_configs;
};
