#include <GUI.hpp>
#include <SDL3/SDL_render.h>

GUI::GUI(SDL_Renderer *renderer) : renderer(renderer) {
  TTF_Init();
  root_container = new Container();
  root_container->set_horizontal_sizing(GUIUnit(0u), GUIUnit(), GUIUnit(0u));
  root_container->set_vertical_sizing(GUIUnit(0u), GUIUnit(), GUIUnit(0u));
}

void GUI::load_fonts(std::vector<struct FontConfig> font_configs) {
  for (struct FontConfig font_config : font_configs)
    fonts[font_config.key] = new Font(font_config, renderer);
}

Font *GUI::get_font(std::string key) const { return fonts.at(key); }

void GUI::add_container(Container *container) {
  root_container->add_container(container);
  container->update(root_container->get_width(), root_container->get_height());
}

void GUI::add_label(Label *label) { labels.push_back(label); }

void GUI::on_window_resize(int width, int height) {
  root_container->update(width, height);
}

void GUI::render() {
  root_container->render(renderer);

  for (const Label *l : labels) {
    SDL_FRect dst = l->get_bounding_rect();
    SDL_RenderTexture(renderer, l->get_texture(), NULL, &dst);
  }
}

GUI::~GUI() {
  for (const auto &it : fonts)
    delete fonts[it.first];
}
