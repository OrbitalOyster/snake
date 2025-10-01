#include <GUI.hpp>
#include <SDL3/SDL_render.h>

GUI::GUI(SDL_Renderer *renderer) : renderer(renderer) {
  TTF_Init();
  root_container = new GUIContainer();
}

void GUI::load_fonts(std::vector<struct FontConfig> font_configs) {
  for (struct FontConfig font_config : font_configs)
    fonts[font_config.key] = new Font(font_config, renderer);
}

/*
void GUI::load_skins(std::vector<struct SkinConfig> skin_configs) {
  for (struct SkinConfig skin_config : skin_configs)
    fonts[skin_config.key] = new GUISkin(skin_config.texture,
      skin_config.center,
      skin_config.top,
      skin_config.top_left,
      skin_config.top_right,
      skin_config.right,
      skin_config.bottom_right,
      skin_config.bottom,
      skin_config.bottom_left,
      skin_config.left
    );
}
*/

void GUI::add_skin(std::string key, GUISkin *skin) { skins[key] = skin; }

Font *GUI::get_font(std::string key) const { return fonts.at(key); }

void GUI::add_container(GUIContainer *container) {
  root_container->add_container(container);
  container->update(root_container->get_width(), root_container->get_height());
}

void GUI::add_label(Label *label) { labels.push_back(label); }

void GUI::add_text(GUIText *text) { texts.push_back(text); }

void GUI::on_window_resize(int width, int height) {
  root_container->update(width, height);
}

void GUI::render() const {
  root_container->render(renderer, 0, 0);
  /*
  for (const Label *l : labels) {
    SDL_FRect dst = l->get_bounding_rect();
    SDL_RenderTexture(renderer, l->get_texture(), NULL, &dst);
  }
  */
  for (GUIText *t : texts) {
    t->render(renderer, root_container);
    // SDL_FRect dst = l->get_bounding_rect();
    // SDL_RenderTexture(renderer, l->get_texture(), NULL, &dst);
  }
}

GUI::~GUI() {
  for (const auto &it : fonts)
    delete fonts[it.first];
}
