#include "SDL3/SDL_init.h"
#include <SDL3/SDL_log.h>
#define SDL_MAIN_USE_CALLBACKS
#include <stdexcept>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdlib.h>

#include <Config.hpp>
#include <Core.hpp>
#include <Font.hpp>

SDL_Texture *goose = NULL;

struct AppState {
  Core *core;
  Font *font;
};

SDL_AppResult SDL_AppInit(void **appstate, [[maybe_unused]] int argc,
                          [[maybe_unused]] char *argv[]) {
  try {
    SDL_Log("Loading config...");
    Config config("config.yaml");
    Core *core = new Core(config);
    Font *font =
        new Font(core->renderer, "assets/fonts/MartianMono-Regular.ttf", 32, 4);
    SDL_Color white = {0xEE, 0xEE, 0xEE, 0xFF};
    SDL_Color black = {0x44, 0x44, 0x44, 0xFF};
    core->hello = font->render_text("Hello, World!", white, black);
    *appstate = new AppState{
        .core = core,
        .font = font,
    };
    return SDL_APP_CONTINUE;
  } catch (const std::runtime_error err) {
    SDL_LogError(1, "Unable to init engine: %s", err.what());
    return SDL_APP_FAILURE;
  }
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  auto app = (struct AppState *)appstate;
  return app->core->on_event(event);
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  auto app = (struct AppState *)appstate;
  app->core->iterate();
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  switch (result) {
  case SDL_APP_CONTINUE: /* Should not happen */
    SDL_Log("Wut?!");
    break;
  case SDL_APP_SUCCESS:
    SDL_Log("Closing gracefully");
    break;
  case SDL_APP_FAILURE:
    SDL_Log("Crashed :(");
    break;
  }
  auto app = (struct AppState *)appstate;
  if (app) {
    delete app->core;
  }
}
