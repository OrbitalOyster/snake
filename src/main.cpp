#include "GUI/Container.hpp"
#include "GUI/Layout.hpp"
#include "GUI/Segment.hpp"
#define SDL_MAIN_USE_CALLBACKS
#include <Config.hpp>
#include <Core.hpp>
#include <GUI.hpp>
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

    GUILayout l1 = GUILayout(GUIUnit(1.0f), GUIUnit(.5f), {}, {});
    GUIContainer *container = new GUIContainer(l1);
    container->set_skin(library->get_skin("window"));
    gui->add_container(container);

    GUILayout l2 = GUILayout(GUIUnit(.5f), GUIUnit(.5f), {}, GUISegment(8u),
                             GUISegment(8u), {});
    GUIContainer *top_right_container = new GUIContainer(l2);
    top_right_container->set_skin(library->get_skin("button"));

    SDL_Cursor *pointerCursor =
        SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_POINTER);
    top_right_container->set_cursor(pointerCursor);
    container->add_container(top_right_container);

    GUILayout l3 = GUILayout(GUIUnit(.4f), GUIUnit(.5f), GUISegment(8u),
                             GUISegment(8u), {}, {});
    GUIContainer *top_left_container = new GUIContainer(l3);
    top_left_container->set_skin(library->get_skin("button"));
    container->add_container(top_left_container);

    GUILayout stoopid_layout = GUILayout(GUISegment(.25f), GUISegment(.5f),
                                         GUISegment(100u), GUISegment(32u));
    GUIContainer *stoopid_container = new GUIContainer(stoopid_layout);

    gui->add_container(stoopid_container);
    stoopid_container->set_skin(library->get_skin("window"));
    stoopid_container->set_min_width(48u);
    stoopid_container->set_min_height(48u);

    SDL_Color white = {0xEE, 0xEE, 0xEE, 0xFF};
    SDL_Color black = {0x44, 0x44, 0x44, 0xFF};
    Font *regular_font = library->get_font("regular");
    GUIText *hello = new GUIText(
        std::string("Hello, World!"), regular_font, white, black,
        {.top = GUISegment(.5f, 0u, .5f), .left = GUISegment(.5f, 0u, .5f)});
    top_right_container->add_text(hello);

    GUILayout movable_layout = GUILayout(GUIUnit(320u), GUIUnit(240u),
                                         GUISegment(100u), GUISegment(800u));
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
