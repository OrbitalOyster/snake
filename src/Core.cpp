#include "SDL3/SDL_timer.h"
#include <Core.hpp>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
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

  /* Set sprite maps */
  for (struct SpriteMapConfig sprite_map_config : config.get_sprite_maps())
    sprite_maps[sprite_map_config.key] = new SpriteMap(sprite_map_config);
}

SDL_Renderer *Core::get_renderer() { return renderer; }

void Core::set_GUI(GUI *new_gui) { gui = new_gui; }

void Core::iterate() {
  SDL_Delay(100);
  /* Clear screen with background color */
  SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g,
                         background_color.b, 0xFF);
  SDL_RenderClear(renderer);
  gui->render();
  render_sprites();
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

SDL_Texture *Core::load_png(std::string filename) {
  SDL_Texture *texture = IMG_LoadTexture(renderer, filename.c_str());
  if (!texture)
    throw std::runtime_error("Failed to load image" +
                             std::string(SDL_GetError()));
  return texture;
}

void Core::render_sprites() {
  SDL_Log("Ticks: %lu", SDL_GetTicks());
  for (const Sprite sprite : sprites) {
  }
}

Core::~Core() {
  if (gui)
    delete gui;
  if (renderer)
    SDL_DestroyRenderer(renderer);
  if (window)
    SDL_DestroyWindow(window);
  SDL_Log("Core destroyed");
}
