#include <Font.hpp>
#include <stdexcept>

Font::Font(const struct FontConfig config)
    : filename(config.filename), size(config.size),
      outline_size(config.outline) {
  ttf = TTF_OpenFont(filename.c_str(), size);
  outline = TTF_OpenFont(filename.c_str(), size);
  if (!ttf || !outline)
    throw std::runtime_error("Unable to open font '" + filename + "' -> " +
                             SDL_GetError());
  TTF_SetFontOutline(outline, outline_size);
  SDL_Log("Loaded font \"%s\", size %f, outline %f", filename.c_str(), size,
          outline_size);
}

TTF_Font *Font::get_ttf() { return ttf; }
TTF_Font *Font::get_outline() { return outline; }
float Font::get_outline_size() { return outline_size; }

Font::~Font() {
  TTF_CloseFont(ttf);
  TTF_CloseFont(outline);
}
