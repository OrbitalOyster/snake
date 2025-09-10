#ifndef GUI_HPP_
#define GUI_HPP_

#include <Container.hpp>
#include <Font.hpp>
#include <GUISkin.hpp>
#include <Label.hpp>
#include <map>
#include <string>
#include <vector>

class GUI {
private:
  SDL_Renderer *renderer;
  std::map<std::string, Font *> fonts;
  std::vector<Label *> labels;
  Container *root_container;
  std::map<std::string, GUISkin *> skins;

public:
  GUI(SDL_Renderer *renderer);
  void load_fonts(std::vector<struct FontConfig> configs);
  void add_skin(std::string key, GUISkin *skin);
  Container *get_root_container() const;
  Font *get_font(std::string key) const;
  void add_container(Container *container);
  void add_label(Label *label);
  void on_window_resize(int width, int height);
  void render();
  ~GUI();
};

#endif
