#include <Config.hpp>
#include <stdexcept>
#include <yaml-cpp/yaml.h>

SDL_Color hex_to_color(unsigned hex) {
  Uint8 r = hex >> 16 & 0xff;
  Uint8 g = hex >> 8 & 0xff;
  Uint8 b = hex & 0xff;
  return {r, g, b, 0xFF};
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
std::vector<struct FontConfig> Config::get_fonts() const { return font_configs; };
