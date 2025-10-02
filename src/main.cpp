#define SDL_MAIN_USE_CALLBACKS
#include <Config.hpp>
#include <Core.hpp>
#include <Font.hpp>
#include <GUI.hpp>
#include <GUI/Skin.hpp>
#include <GUI/Unit.hpp>
#include <Library.hpp>
#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <iostream>
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

    /*
    gui->load_fonts(config.get_fonts());

    GUISkin *skin = new GUISkin(
        core->get_texture("gui_skin"), {96, 32, 16, 16}, {80, 16, 16, 16},
        {96, 16, 16, 16}, {112, 16, 16, 16}, {112, 32, 16, 16}, {112, 48, 16,
   16}, {96, 48, 16, 16}, {80, 48, 16, 16}, {80, 32, 16, 16});
    gui->add_skin("test_skin", skin);

    GUIContainer *bottom_container =
        new GUIContainer(GUISizing(GUIUnit(32u), GUIUnit(), GUIUnit(32u)),
                         GUISizing(GUIUnit(), GUIUnit(.25f), GUIUnit(32u)));
    bottom_container->add_container(top_right_container);
    bottom_container->set_skin(skin);
    bottom_container->set_min_width(GUIUnit(400u + 8u));

    gui->add_container(bottom_container);

    GUIContainer *centered_container = new GUIContainer(
        GUISizing(GUIUnit(.5f), GUIUnit(320u), GUIUnit(), GUIUnit(-.5f)),
        GUISizing(GUIUnit(.5f), GUIUnit(240u), GUIUnit(), GUIUnit(-.5f)));
    gui->add_container(centered_container);

   Label *hello = new Label(std::string("Hello, World!"), 16, 16,
                             gui->get_font("regular"), white, black);
    gui->add_label(hello);

    Sprite *apple = new Sprite(64, 64, 128, 128, core->get_texture("apple"),
                               core->get_sprite_map("apple_default"));
    core->add_sprite(apple);

    Sprite *goose = new Sprite(256, 64, 128, 128, core->get_texture("goose"));
    core->add_sprite(goose);
    */

    /* Library */
    Library *library = new Library(core->get_renderer());
    config.load_images_to_library(library);
    config.load_fonts_to_library(library, core->get_renderer());
    config.load_sprite_maps_to_library(library);
    config.load_skins_to_library(library);

    Sprite *apple = new Sprite(0, 0, 128, 128, library->get_texture("apple"),
                               library->get_sprite_map("apple_default"));
    core->add_sprite(apple);

    /*
    GUIContainer *container =
        new GUIContainer({.height = .5f,
                          .top = GUISegment(0u, 0u, 0u),
                          .left = GUISegment(0u, 0u, 0u),
                          .right = GUISegment(0u, 0u, 0u)});
    container->set_skin(skin);
    gui->add_container(container);

    GUIContainer *top_right_container =
        new GUIContainer({.width = .5f,
                          .height = .5f,
                          .top = GUISegment(8u),
                          .right = GUISegment(8u)});
    top_right_container->set_skin(skin);
    container->add_container(top_right_container);

    GUIContainer *stoopid_container =
        new GUIContainer({.top = GUISegment(.5f, 0u, 0u),
                          .left = GUISegment(.25f),
                          .bottom = GUISegment(32u),
                          .right = GUISegment(100u)});

    gui->add_container(stoopid_container);
    stoopid_container->set_skin(skin);
    stoopid_container->set_min_width(48u);
    stoopid_container->set_min_height(48u);

    SDL_Color white = {0xEE, 0xEE, 0xEE, 0xFF};
    SDL_Color black = {0x44, 0x44, 0x44, 0xFF};
    GUIText *hello = new GUIText(
        std::string("Hello, World!"), gui->get_font("regular"), white, black,
        {.top = GUISegment(.5f, 0u, .5f), .left = GUISegment(.5f, 0u, .5f)});
    gui->add_text(hello);
    */

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
