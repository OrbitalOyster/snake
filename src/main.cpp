#define SDL_MAIN_USE_CALLBACKS
#include <Config.hpp>
#include <Core.hpp>
#include <GUI.hpp>
#include <GUI/Text.hpp>
#include <GUI/Unit.hpp>
#include <Library.hpp>
#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
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
    config.load_textures_to_library(library);
    config.load_fonts_to_library(library);
    config.load_sprite_maps_to_library(library);
    config.load_stretchables_to_library(library);
    config.load_skins_to_library(library);

    Sprite *apple = new Sprite(0, 320, 128, 128, library->get_texture("apple"),
                               library->get_sprite_map("apple_default"));
    Sprite *cross = new Sprite(8, 8, 16, 16, library->get_texture("gui_skin"),
                               library->get_sprite_map("cross"));
    core->add_sprite(apple);

    GUILayout upper_half_layout = GUILayout(1.0, .5, {}, {});
    GUIContainer *upper_half_container =
        new GUIContainer("upper half", upper_half_layout);
    upper_half_container->set_skin(library->get_skin("window"));
    gui->add_container(upper_half_container);

    GUILayout top_right_layout = GUILayout(.5, .5, {}, GUIUnit(8.0, Absolute),
                                           GUIUnit(8.0, Absolute), {});
    GUIContainer *top_right_container =
        new GUIContainer("top right", top_right_layout);
    top_right_container->set_skin(library->get_skin("button"));

    SDL_Color white = {0xEE, 0xEE, 0xEE, 0xFF};
    SDL_Color black = {0x44, 0x44, 0x44, 0xFF};
    Font *regular_font = library->get_font("regular");
    TextLayout center =
        TextLayout(GUISegment(.5, 0.0, .5), GUISegment(.5, 0.0, .5));
    GUIText *hello = new GUIText(std::string("Hello, World!"), regular_font,
                                 white, black, center);
    top_right_container->add_text(hello);
    upper_half_container->add_container(top_right_container);

    GUILayout top_left_layout =
        GUILayout(GUIUnit(100.0, Absolute), GUIUnit(150.0, Absolute),
                  GUISegment(GUIUnit(8.0, Absolute)),
                  GUISegment(GUIUnit(8.0, Absolute)), {}, {});
    GUIContainer *top_left_container =
        new GUIContainer("top left", top_left_layout);
    top_left_container->set_skin(library->get_skin("button"));
    upper_half_container->add_container(top_left_container);

    GUILayout stoopid_layout =
        GUILayout(GUISegment(GUIUnit(.25)), GUISegment(GUIUnit(.5)),
                  GUISegment(GUIUnit(100.0, Absolute)),
                  GUISegment(GUIUnit(32.0, Absolute)));
    GUIContainer *stoopid_container =
        new GUIContainer("stoopid", stoopid_layout);

    gui->add_container(stoopid_container);
    stoopid_container->set_skin(library->get_skin("window"));
    stoopid_container->set_min_width(GUIUnit(48.0, Absolute));
    stoopid_container->set_min_height(GUIUnit(48.0, Absolute));

    GUILayout close_button_layout =
        GUILayout(GUIUnit(32.0, Absolute), GUIUnit(32.0, Absolute), {},
                  GUIUnit(8.0, Absolute), GUIUnit(8.0, Absolute), {});
    GUIContainer *close_button =
        new GUIContainer("close_button", close_button_layout);
    close_button->set_skin(library->get_skin("button"));
    close_button->add_sprite(cross);
    close_button->set_cursor(gui->get_system_cursor("pointer"));

    stoopid_container->add_container(close_button);

    GUILayout movable_layout = GUILayout(
        GUIUnit(320, Absolute), GUIUnit(240, Absolute),
        GUISegment(GUIUnit(200, Absolute)), GUISegment(GUIUnit(600, Absolute)));
    GUIContainer *movable_container =
        new GUIContainer("movable", movable_layout);
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
