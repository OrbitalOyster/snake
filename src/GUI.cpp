#include "SDL3_ttf/SDL_ttf.h"
#include <GUI.hpp>
#include <stdexcept>

GUI::GUI(SDL_Renderer *renderer) : renderer(renderer) { TTF_Init(); }

void GUI::load_fonts(std::vector<struct FontConfig> font_configs) {
  for (struct FontConfig font_config : font_configs)
    fonts[font_config.key] = new Font(font_config);
}

SDL_Texture *GUI::render_text(const std::string text, TTF_Font *ttf_font,
                              SDL_Color color) {
  /* Create surface from font */
  SDL_Surface *tmp_surface =
      TTF_RenderText_Blended(ttf_font, text.c_str(), 0, color);
  if (!tmp_surface)
    throw std::runtime_error("Unable to create surface from font -> " +
                             std::string(SDL_GetError()));
  /* Convert surface to texture */
  SDL_Texture *result = SDL_CreateTextureFromSurface(renderer, tmp_surface);
  if (result == NULL)
    throw std::runtime_error("Unable to create texture from font -> " +
                             std::string(SDL_GetError()));
  /* Free tmp surface */
  SDL_DestroySurface(tmp_surface);
  return result;
}

SDL_Texture *GUI::render_text(const std::string text, std::string font_key,
                              SDL_Color color, SDL_Color outline_color) {
  if (!fonts[font_key])
    throw std::runtime_error("Invalid font key: " + font_key);
  Font *font = fonts[font_key];
  /* Outline text on background */
  SDL_Texture *bg = render_text(text, font->get_outline(), outline_color);
  /* Actual text on foreground */
  SDL_Texture *fg = render_text(text, font->get_ttf(), color);
  /* Get bg dimensions */
  float bw, bh;
  SDL_GetTextureSize(bg, &bw, &bh);
  SDL_Log("%f %f\n", bw, bh);
  /*  Get fg dimensions */
  float fw, fh;
  SDL_GetTextureSize(fg, &fw, &fh);
  SDL_Log("%f %f\n", fw, fh);
  /* Transparent background */
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
  SDL_Texture *result = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
                                          SDL_TEXTUREACCESS_TARGET, bw, bh);
  SDL_SetTextureBlendMode(result, SDL_BLENDMODE_BLEND);
  SDL_SetRenderTarget(renderer, result);
  // TODO: Need this?
  // SDL_RenderClear(renderer);
  const SDL_FRect bg_rect = {0, 0, bw, bh};
  const SDL_FRect fg_rect = {font->get_outline_size(), font->get_outline_size(),
                             fw, fh};
  /* Copy bg, fg, clear render target */
  SDL_RenderTexture(renderer, bg, NULL, &bg_rect);
  SDL_RenderTexture(renderer, fg, NULL, &fg_rect);
  SDL_SetRenderTarget(renderer, NULL);
  /* Clean up */
  SDL_DestroyTexture(bg);
  SDL_DestroyTexture(fg);
  /* Done */
  return result;
}

void GUI::add_label(Label *label) {
  labels.push_back(label);
}

void GUI::render() {
  for (const Label *l : labels) {

  }
}
