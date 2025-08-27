#include "SDL3/SDL_stdinc.h"
#include <Config.hpp>
#include <stdexcept>
#include <yaml-cpp/yaml.h>

SDL_Color hex_to_color(unsigned hex) {
  Uint8 r = hex >> 16 & 0xff;
  Uint8 g = hex >> 8 & 0xff;
  Uint8 b = hex & 0xff;
  return { r, g, b, 0xFF };
}

Config::Config(std::string filename) {
  try {
    YAML::Node config = YAML::LoadFile(filename);
    YAML::Node window = config["window"];
    title = window["title"].as<std::string>();
    window_width = window["width"].as<int>();
    window_height = window["height"].as<int>();
    background_color = hex_to_color(window["background-color"].as<unsigned int>());
    fullscreen = window["fullscreen"].as<bool>();
    resizeable = window["resizeable"].as<bool>();
  } catch (const std::runtime_error err) {
    throw std::runtime_error(
        std::string("Unable to load config " + filename + ": ") + err.what());
  }
}

std::string Config::get_title() const { return title; };
int Config::get_window_width() const { return window_width; }
int Config::get_window_height() const { return window_height; }
