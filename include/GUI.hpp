#ifndef GUI_HPP_
#define GUI_HPP_

#include <Font.hpp>
#include <GUI/Container.hpp>
#include <GUI/Skin.hpp>
#include <GUI/Text.hpp>
#include <Label.hpp>
#include <map>
#include <string>
#include <vector>

class GUI {
private:
  SDL_Renderer *renderer;
  std::map<std::string, Font *> fonts;
  std::vector<Label *> labels;
  std::vector<GUIText *> texts;
  GUIContainer *root_container;
  std::map<std::string, GUISkin *> skins;

public:
  GUI(SDL_Renderer *renderer);
  void load_fonts(std::vector<struct FontConfig> configs);
  void load_skins(std::vector<struct SkinConfig> skin_configs);
  void add_skin(std::string key, GUISkin *skin);
  GUIContainer *get_root_container() const;
  Font *get_font(std::string key) const;
  void add_container(GUIContainer *container);
  void add_label(Label *label);
  void add_text(GUIText *text);
  void on_window_resize(int width, int height);
  void render() const;
  ~GUI();
};

#endif
