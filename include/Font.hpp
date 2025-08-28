#ifndef FONT_HPP_
#define FONT_HPP_

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

struct FontConfig {
  std::string key;
  std::string filename;
  float size;
  float outline;
};

class Font {
private:
  const std::string filename;
  TTF_Font *ttf;
  float size;
  TTF_Font *outline;
  float outline_size;

public:
  Font(const struct FontConfig config);
  TTF_Font *get_ttf();
  TTF_Font *get_outline();
  float get_outline_size();
  ~Font();
};

#endif
