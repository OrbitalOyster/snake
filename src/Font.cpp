#include <Font.hpp>
#include <stdexcept>

Font::Font(const struct FontConfig config, SDL_Renderer *renderer)
    : filename(config.filename), size(config.size),
      outline_size(config.outline), renderer(renderer) {
  ttf = TTF_OpenFont(filename.c_str(), size);
  outline = TTF_OpenFont(filename.c_str(), size);
  if (!ttf || !outline)
    throw std::runtime_error("Unable to open font '" + filename + "' -> " +
                             SDL_GetError());
  TTF_SetFontOutline(outline, outline_size);
  SDL_Log("Loaded font \"%s\", size %f, outline %f", filename.c_str(), size,
          outline_size);
}

SDL_Texture *Font::render_text(const std::string text, TTF_Font *ttf_font,
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

SDL_Texture *Font::get_texture(const std::string text, SDL_Color color,
                               SDL_Color outline_color, float *w, float *h) {
  /* Outline text on background */
  SDL_Texture *bg = render_text(text, outline, outline_color);
  /* Actual text on foreground */
  SDL_Texture *fg = render_text(text, ttf, color);
  /* Get bg dimensions */
  float bw, bh;
  SDL_GetTextureSize(bg, &bw, &bh);
  /*  Get fg dimensions */
  float fw, fh;
  SDL_GetTextureSize(fg, &fw, &fh);
  /* Transparent background */
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
  SDL_Texture *result = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
                                          SDL_TEXTUREACCESS_TARGET, bw, bh);
  SDL_SetTextureBlendMode(result, SDL_BLENDMODE_BLEND);
  SDL_SetRenderTarget(renderer, result);
  // TODO: Need this?
  // SDL_RenderClear(renderer);
  const SDL_FRect bg_rect = {0, 0, bw, bh};
  const SDL_FRect fg_rect = {outline_size, outline_size, fw, fh};

  *w = bw;
  *h = bh;

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

Font::~Font() {
  TTF_CloseFont(ttf);
  TTF_CloseFont(outline);
  SDL_Log("Cleaned up font %s", filename.c_str());
}
