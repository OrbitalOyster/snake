#include <GUI.hpp>

GUI::GUI(SDL_Renderer *renderer) : renderer(renderer) { TTF_Init(); }

void GUI::load_fonts(std::vector<struct FontConfig> font_configs) {
  for (struct FontConfig font_config : font_configs)
    fonts[font_config.key] = new Font(font_config, renderer);
}

Font *GUI::get_font(std::string key) {
  return fonts[key];
}

void GUI::add_label(Label *label) {
  labels.push_back(label);
}

void GUI::render() {
  for (const Label *l : labels) {
    SDL_FRect dstRect = l->get_bounding_rect();
    SDL_RenderTexture(renderer, l->get_texture(), NULL, &dstRect);
  }
}

GUI::~GUI() {
  for (const auto &pair : fonts)
    delete fonts[pair.first];
}
