#include <Core.hpp>
#include <SDL3/SDL_log.h>
#include <stdexcept>

Core::Core(Config config) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    throw std::runtime_error("Unable to initialize SDL (" +
                             std::string(SDL_GetError()) + " )");
  }
  if (!SDL_CreateWindowAndRenderer(
          config.get_title().c_str(), config.get_window_width(),
          config.get_window_height(),
          SDL_WINDOW_FULLSCREEN * config.get_fullscreen() |
              SDL_WINDOW_RESIZABLE * config.get_resizeable(),
          &window, &renderer)) {
    throw std::runtime_error("Unable to initialize renderer (" +
                             std::string(SDL_GetError()) + " )");
  }
  background_color = config.get_background_color();
}

void Core::iterate() {
  SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g,
                         background_color.b, 0xFF);
  SDL_RenderClear(renderer);
  SDL_FRect dstRect = {16, 16, 294, 47};
  SDL_RenderTexture(renderer, hello, NULL, &dstRect);
  SDL_RenderPresent(renderer);
}

SDL_AppResult Core::on_event(SDL_Event *event) {
  /* Esc key */
  if (event->type == SDL_EVENT_KEY_DOWN &&
      event->key.scancode == SDL_SCANCODE_ESCAPE)
    return SDL_APP_SUCCESS;
  /* Quit event */
  if (event->type == SDL_EVENT_QUIT)
    return SDL_APP_SUCCESS;

  return SDL_APP_CONTINUE;
}

SDL_Texture *Core::load_png(const char *filename) {
  SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
  if (!texture) {
    SDL_Log("Failed to load asset: %s", SDL_GetError());
    return NULL;
  }
  return texture;
}

Core::~Core() {
  if (renderer)
    SDL_DestroyRenderer(renderer);
  if (window)
    SDL_DestroyWindow(window);
  SDL_Log("Core destroyed");
}
