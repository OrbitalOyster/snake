#include <GUI.hpp>
#include <SDL3/SDL_render.h>

GUI::GUI(SDL_Renderer *renderer) : renderer(renderer) {
  TTF_Init();
  root_container = new Container(0, 0, 0, 0);
  containers.push_back(root_container);
}

void GUI::load_fonts(std::vector<struct FontConfig> font_configs) {
  for (struct FontConfig font_config : font_configs)
    fonts[font_config.key] = new Font(font_config, renderer);
}

Font *GUI::get_font(std::string key) const { return fonts.at(key); }

void GUI::add_container(Container *container) {
  containers.push_back(container);
}

void GUI::add_label(Label *label) { labels.push_back(label); }

void GUI::on_window_resize(int width, int height) {
  root_container->resize(width, height);
}

void GUI::render() {
  for (const Container *c : containers) {
    const SDL_FRect dst = c->get_bounding_rect();
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0, 0xFF);
    SDL_RenderRect(renderer, &dst);
  }

  for (const Label *l : labels) {
    SDL_FRect dst = l->get_bounding_rect();
    SDL_RenderTexture(renderer, l->get_texture(), NULL, &dst);
  }
}

GUI::~GUI() {
  for (const auto &pair : fonts)
    delete fonts[pair.first];
}
