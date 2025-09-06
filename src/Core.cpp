#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_timer.h"
#include "SpriteMap.hpp"
#include <Core.hpp>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <stdexcept>
#include <string>

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

  /* No ugly scaling */
  SDL_SetDefaultTextureScaleMode(renderer, SDL_SCALEMODE_NEAREST);

  /* Load images */
  for (struct ImageConfig image_config : config.get_images())
    textures[image_config.key] = load_png(image_config.filename);

  /* Set sprite maps */
  for (struct SpriteMapConfig sprite_map_config : config.get_sprite_maps())
    sprite_maps[sprite_map_config.key] = new SpriteMap(
        sprite_map_config, textures.at(sprite_map_config.texture));
}

SDL_Renderer *Core::get_renderer() { return renderer; }

void Core::set_GUI(GUI *new_gui) { gui = new_gui; }

void Core::iterate() {
  SDL_Delay(10);
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
  SDL_Log("Loaded texture %s", filename.c_str());
  return texture;
}

const SpriteMap *Core::get_sprite_map(std::string key) const {
  if (sprite_maps.find(key) != sprite_maps.end())
    return sprite_maps.at(key);
  else
    throw std::runtime_error("Invalid sprite map: " + key);
}

void Core::add_sprite(Sprite *sprite) { sprites.push_back(sprite); }

void Core::render_sprites() {
  unsigned long ticks = SDL_GetTicks();
  for (const Sprite *sprite : sprites)
    sprite->render(ticks, renderer);
}

Core::~Core() {
  if (gui)
    delete gui;
  for (auto it = textures.begin(); it != textures.end(); ++it)
      SDL_DestroyTexture(textures[it->first]);
  if (renderer)
    SDL_DestroyRenderer(renderer);
  if (window)
    SDL_DestroyWindow(window);
  SDL_Log("Core destroyed");
}
