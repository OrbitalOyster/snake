#ifndef GUI_FONT_HPP_
#define GUI_FONT_HPP_

#include <SDL3_ttf/SDL_ttf.h>
#include <string>

class Font {
private:
  const std::string filename;
  TTF_Font *ttf;
  float size;
  TTF_Font *outline;
  float outline_size;
  SDL_Renderer *renderer;
  SDL_Texture *render_text(const std::string text, TTF_Font *font,
                           SDL_Color color);

public:
  Font(std::string filename, float size, float outline_size,
       SDL_Renderer *renderer);
  SDL_Texture *get_texture(const std::string text, SDL_Color color,
                           SDL_Color outline_color, float *w, float *h);
  ~Font();
};

#endif
