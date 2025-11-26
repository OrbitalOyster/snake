#define SDL_MAIN_USE_CALLBACKS
#include <Config.hpp>
#include <Core.hpp>
#include <GUI.hpp>
#include <GUI/Text.hpp>
#include <GUI/Unit.hpp>
#include <Library.hpp>
#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <Stretchable.hpp>
#include <stdexcept>
#include <stdlib.h>

SDL_AppResult SDL_AppInit(void **appstate, [[maybe_unused]] int argc,
                          [[maybe_unused]] char *argv[]) {

  try {
    /* Get config */
    SDL_Log("Loading config...");
    Config config("config.yaml");
    /* Create core */
    Core *core = new Core(config);
    *appstate = core;
    /* Create GUI */
    GUI *gui = new GUI(core->get_renderer());
    core->set_GUI(gui);
    /* Library */
    Library *library = new Library(core->get_renderer());
    config.load_images_to_library(library);
    config.load_fonts_to_library(library);
    config.load_sprite_maps_to_library(library);
    config.load_stretchables_to_library(library);
    config.load_skins_to_library(library);

    Sprite *apple = new Sprite(0, 320, 128, 128, library->get_texture("apple"),
                               library->get_sprite_map("apple_default"));
    core->add_sprite(apple);

    GUILayout l1 = GUILayout(1.0f, .5f, {}, {});
    GUIContainer *container = new GUIContainer(l1);
    container->set_skin(library->get_skin("window"));
    gui->add_container(container);

    GUILayout top_right_layout =
        GUILayout(.5f, .5f, {}, GUIUnit(8, Absolute), GUIUnit(8, Absolute), {});
    GUIContainer *top_right_container = new GUIContainer(top_right_layout);
    top_right_container->set_skin(library->get_skin("button"));

    SDL_Cursor *pointerCursor =
        SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_POINTER);
    top_right_container->set_cursor(pointerCursor);
    container->add_container(top_right_container);

    GUILayout top_left_layout =
        GUILayout(.4f, .5f, GUISegment(GUIUnit(8.0f, Absolute)),
                  GUISegment(GUIUnit(8.0f, Absolute)), {}, {});
    GUIContainer *top_left_container = new GUIContainer(top_left_layout);
    top_left_container->set_skin(library->get_skin("button"));
    container->add_container(top_left_container);

    GUILayout stoopid_layout = GUILayout(
        GUISegment(GUIUnit(.25f), 0, GUIUnit(0, Absolute)), GUISegment(GUIUnit(.5f)),
        GUISegment(GUIUnit(100, Absolute), 0, GUIUnit(0, Absolute)), GUISegment(GUIUnit(32, Absolute)));
    GUIContainer *stoopid_container = new GUIContainer(stoopid_layout);

    gui->add_container(stoopid_container);
    stoopid_container->set_skin(library->get_skin("window"));
    stoopid_container->set_min_width(GUIUnit(48, Absolute));
    stoopid_container->set_min_height(GUIUnit(48, Absolute));

    SDL_Color white = {0xEE, 0xEE, 0xEE, 0xFF};
    SDL_Color black = {0x44, 0x44, 0x44, 0xFF};
    Font *regular_font = library->get_font("regular");
    TextLayout centered =
        TextLayout(GUISegment(.5f, 0, .5f), GUISegment(.5f, 0u, .5f));
    GUIText *hello = new GUIText(std::string("Hello, World!"), regular_font,
                                 white, black, centered);
    top_right_container->add_text(hello);

    GUILayout movable_layout = GUILayout(
        GUIUnit(320, Absolute), GUIUnit(240, Absolute),
        GUISegment(GUIUnit(200, Absolute)), GUISegment(GUIUnit(600, Absolute)));
    GUIContainer *movable_container = new GUIContainer(movable_layout);
    movable_container->set_skin(library->get_skin("window"));
    movable_container->set_draggable(true);
    gui->add_container(movable_container);

    return SDL_APP_CONTINUE;
  } catch (const std::runtime_error err) {
    SDL_LogError(1, "Unable to init engine -> %s", err.what());
    return SDL_APP_FAILURE;
  }
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  Core *core = (Core *)appstate;
  return core->on_event(event);
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  Core *core = (Core *)appstate;
  core->iterate();
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
  Core *core = (Core *)appstate;
  if (core)
    delete core;
}
