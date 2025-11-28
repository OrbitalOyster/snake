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
  /* No ugly scaling */
  SDL_SetDefaultTextureScaleMode(renderer, SDL_SCALEMODE_NEAREST);
}

SDL_Renderer *Core::get_renderer() { return renderer; }

void Core::set_GUI(GUI *new_gui) {
  gui = new_gui;
  gui->reset_focus();
}

void Core::render() {
  /* Clear screen with background color */
  SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g,
                         background_color.b, 0xFF);
  SDL_RenderClear(renderer);
  render_sprites();
  gui->render();
  SDL_RenderPresent(renderer);
}

void Core::iterate() {
  SDL_Delay(10);
  render();
}

SDL_AppResult Core::on_event(SDL_Event *event) {
  switch (event->type) {
  /* Resize event */
  case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
    int w, h;
    SDL_GetWindowSizeInPixels(window, &w, &h);
    SDL_Log("Window resize: %ix%i", w, h);
    gui->on_window_resize(w, h);
    render();
    break;
  /* Esc key */
  case SDL_EVENT_KEY_DOWN:
    if (event->key.scancode == SDL_SCANCODE_ESCAPE)
      return SDL_APP_SUCCESS;
    else
      break;
  /* Quit event */
  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;
  /* Mouse move */
  case SDL_EVENT_MOUSE_MOTION:
    gui->on_mouse_move(event->motion.x - event->motion.xrel,
                       event->motion.y - event->motion.yrel, event->motion.x,
                       event->motion.y);
    break;
  /* Mouse down */
  case SDL_EVENT_MOUSE_BUTTON_DOWN:
    gui->on_mouse_down(event->motion.x, event->motion.y);
    break;
  /* Mouse up */
  case SDL_EVENT_MOUSE_BUTTON_UP:
    gui->on_mouse_up(event->motion.x, event->motion.y);
    break;
  case SDL_EVENT_WINDOW_FOCUS_GAINED:
    SDL_Log("SDL_EVENT_WINDOW_FOCUS_GAINED");
    break;
  case SDL_EVENT_WINDOW_MOUSE_ENTER:
    SDL_Log("SDL_EVENT_WINDOW_MOUSE_ENTER");
    gui->reset_mouse();
    break;
  case SDL_EVENT_WINDOW_MOUSE_LEAVE:
    SDL_Log("SDL_EVENT_WINDOW_MOUSE_LEAVE");
    gui->reset_focus();
    break;
  case SDL_EVENT_WINDOW_FOCUS_LOST:
    SDL_Log("SDL_EVENT_WINDOW_FOCUS_LOST");
    gui->reset_focus();
    break;
  }

  return SDL_APP_CONTINUE;
}

void Core::add_sprite(Sprite *sprite) { sprites.push_back(sprite); }

void Core::render_sprites() {
  unsigned long ticks = SDL_GetTicks();
  for (const Sprite *sprite : sprites)
    sprite->render(ticks);
}

Core::~Core() {
  if (renderer)
    SDL_DestroyRenderer(renderer);
  if (window)
    SDL_DestroyWindow(window);
  SDL_Log("Core destroyed");
}
