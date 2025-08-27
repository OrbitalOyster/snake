#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>

int main(int argc, char *argv[]) {
  std::string filename = "config.yaml";
  YAML::Node config = YAML::LoadFile(filename);
  YAML::Node window = config["window"];
  std::string title = window["title"].as<std::string>();
  int window_width = window["width"].as<int>();
  int window_height = window["height"].as<int>();

  std::cout << title << std::endl;
  std::cout << window_width << std::endl;
  std::cout << window_height << std::endl;
}
