#ifndef GUI_HPP_
#define GUI_HPP_

#include <GUI/Container.hpp>
#include <GUI/Font.hpp>
#include <GUI/Skin.hpp>
#include <GUI/Text.hpp>
#include <vector>

class GUI {
private:
  SDL_Renderer *renderer;
  std::vector<GUIText *> texts;
  GUIContainer *root_container;

public:
  GUI(SDL_Renderer *renderer);
  GUIContainer *get_root_container() const;
  void add_container(GUIContainer *container);
  void add_text(GUIText *text);
  void on_window_resize(int width, int height);
  void render() const;
  ~GUI();
};

#endif
