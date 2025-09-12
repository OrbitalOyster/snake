#define SDL_MAIN_USE_CALLBACKS
#include <Config.hpp>
#include <Core.hpp>
#include <Font.hpp>
#include <GUI.hpp>
#include <GUISizing.hpp>
#include <GUISkin.hpp>
#include <GUIUnit.hpp>
#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
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
    /* Create GUI */
    GUI *gui = new GUI(core->get_renderer());
    core->set_GUI(gui);
    gui->load_fonts(config.get_fonts());

    /*
     * center": [ 32, 32, 16, 16 ],
     * topLeft": [ 16, 16, 16, 16 ],
     * top": [ 32, 16, 16, 16 ],
     * topRight": [ 48, 16, 16, 16 ],
     * right": [ 48, 32, 16, 16 ],
     * bottomRight": [ 48, 48, 16, 16 ],
     * bottom": [ 32, 48, 16, 16 ],
     * bottomLeft": [ 16, 48, 16, 16 ]
     * left": [ 16, 32, 16, 16 ],
     */

    GUISkin *skin = new GUISkin(
        core->get_texture("gui_skin"), {32, 32, 16, 16}, {16, 16, 16, 16},
        {32, 16, 16, 16}, {48, 16, 16, 16}, {48, 32, 16, 16}, {48, 48, 16, 16},
        {32, 48, 16, 16}, {16, 48, 16, 16}, {16, 32, 16, 16});
    gui->add_skin("test_skin", skin);

    Container *top_right_container =
        new Container(GUISizing(GUIUnit(.5f), GUIUnit(), GUIUnit(4u)),
                      GUISizing(GUIUnit(4u), GUIUnit(), GUIUnit(.5f)));

    Container *bottom_container =
        new Container(GUISizing(GUIUnit(32u), GUIUnit(), GUIUnit(32u)),
                      GUISizing(GUIUnit(), GUIUnit(.25f), GUIUnit(32u)));

    bottom_container->add_container(top_right_container);
    bottom_container->set_skin(skin);

    gui->add_container(bottom_container);

    Container *centered_container = new Container(
        GUISizing(GUIUnit(.5f), GUIUnit(320u), GUIUnit(), GUIUnit(-.5f)),
        GUISizing(GUIUnit(.5f), GUIUnit(240u), GUIUnit(), GUIUnit(-.5f)));
    gui->add_container(centered_container);

    SDL_Color white = {0xEE, 0xEE, 0xEE, 0xFF};
    SDL_Color black = {0x44, 0x44, 0x44, 0xFF};
    Label *hello = new Label(std::string("Hello, World!"), 16, 16,
                             gui->get_font("regular"), white, black);
    gui->add_label(hello);

    Sprite *apple = new Sprite(64, 64, 128, 128, core->get_texture("apple"),
                               core->get_sprite_map("apple_default"));
    core->add_sprite(apple);

    Sprite *goose = new Sprite(256, 64, 128, 128, core->get_texture("goose"));
    core->add_sprite(goose);

    *appstate = core;
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
