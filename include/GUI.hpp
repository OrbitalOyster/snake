#ifndef GUI_HPP_
#define GUI_HPP_

#include <Container.hpp>
#include <Font.hpp>
#include <Label.hpp>
#include <map>
#include <string>
#include <vector>

class GUI {
private:
  SDL_Renderer *renderer;
  std::map<std::string, Font *> fonts;
  std::vector<Label *> labels;
  std::vector<Container *> containers;

public:
  GUI(SDL_Renderer *renderer);
  void load_fonts(std::vector<struct FontConfig> configs);
  Font *get_font(std::string key) const;
  void add_container(Container *container);
  void add_label(Label *label);
  void render();
  ~GUI();
};

#endif
