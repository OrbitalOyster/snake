#include <GUI/Container.hpp>
#include <optional>
#include <stdexcept>

GUIContainer::GUIContainer() {}

GUIContainer::GUIContainer(ContainerLayout layout) {
  /* Actual lunacy */
  width = layout.width.has_value() ? layout.width : std::nullopt;
  height = layout.height.has_value() ? layout.height : std::nullopt;
  top = layout.top.has_value() ? layout.top : std::nullopt;
  left = layout.left.has_value() ? layout.left : std::nullopt;
  bottom = layout.bottom.has_value() ? layout.bottom : std::nullopt;
  right = layout.right.has_value() ? layout.right : std::nullopt;
}

SDL_FRect GUIContainer::calculate(ContainerLayout layout, float parent_width,
                                  float parent_height) {
  float x, y, w, h;
  /* Width is set */
  if (layout.width.has_value()) {
    w = layout.width->to_pixels(parent_width);
    if (layout.left.has_value()) {
      if (layout.right.has_value())
        throw std::runtime_error("Redundant right value");
      x = layout.left->calculate(parent_width, w);
    } else if (layout.right.has_value()) {
      if (layout.left.has_value())
        throw std::runtime_error("Redundant left value");
      float right_p = layout.right->calculate(parent_width, w);
      x = parent_width - w - right_p;
    } else {
      throw std::runtime_error(
          "Invalid horizontal sizing (left and right empty)");
    }
  } else /* Dynamic width */
  {
    if (!layout.left.has_value() || !layout.right.has_value())
      throw std::runtime_error(
          "Invalid horizontal sizing (left or right empty)");
    x = layout.left->calculate(parent_width);
    float right_p = layout.right->calculate(parent_width);
    w = parent_width - x - right_p;
  }

  /* Height is set */
  if (layout.height.has_value()) {
    h = layout.height->to_pixels(parent_height);
    if (layout.top.has_value()) {
      if (layout.bottom.has_value())
        throw std::runtime_error("Redundant bottom value");
      y = layout.top->calculate(parent_height, h);
    } else if (layout.bottom.has_value()) {
      if (layout.top.has_value())
        throw std::runtime_error("Redundant top value");
      float bottom_p = layout.bottom->calculate(parent_height, h);
      y = parent_height - h - bottom_p;
    } else {
      throw std::runtime_error("Invalid vertical sizing");
    }
  } else /* Dynamic height */
  {
    if (!layout.top.has_value() || !layout.bottom.has_value())
      throw std::runtime_error("Invalid vertical sizing");
    y = layout.top->calculate(parent_height);
    float bottom_p = layout.bottom->calculate(parent_height);
    h = parent_height - y - bottom_p;
  }

  return {.x = x, .y = y, .w = w, .h = h};
}

void GUIContainer::update(int parent_width, int parent_height) {
  int old_w = rect.w, old_h = rect.h;
  rect = calculate({width, height, top, left, bottom, right}, parent_width,
                   parent_height);

  /* Adjust min. size */
  if (rect.w < min_width.to_pixels(parent_width))
    rect.w = min_width.to_pixels(parent_width);
  if (rect.h < min_height.to_pixels(parent_height))
    rect.h = min_height.to_pixels(parent_height);

  if (rect.w != old_w || rect.h != old_h)
    cache_is_outdated = true;

  for (GUIContainer *c : children)
    c->update(rect.w, rect.h);
}

void GUIContainer::set_skin(GUISkin *skin) {
  this->skin = skin;
  cache_is_outdated = true;
}

void GUIContainer::set_min_width(GUIUnit min_width) {
  this->min_width = min_width;
}

void GUIContainer::set_min_height(GUIUnit min_height) {
  this->min_height = min_height;
}

SDL_FRect GUIContainer::get_bounding_rect() const { return rect; }

int GUIContainer::get_width() const { return rect.w; }
int GUIContainer::get_height() const { return rect.h; }

void GUIContainer::add_container(GUIContainer *container) {
  children.push_back(container);
  children.back()->update(rect.w, rect.h);
}

void GUIContainer::update_cache(SDL_Renderer *renderer) {
  if (cache != NULL)
    SDL_DestroyTexture(cache);
  cache = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
                            SDL_TEXTUREACCESS_TARGET, rect.w, rect.h);
  SDL_SetRenderTarget(renderer, cache);
  skin->render({0, 0, rect.w, rect.h});
  SDL_SetRenderTarget(renderer, NULL);
  cache_is_outdated = false;
}

void GUIContainer::render(SDL_Renderer *renderer, int parent_x, int parent_y) {
  SDL_FRect dst = get_bounding_rect();
  if (!dst.w || !dst.h)
    return;
  dst.x += parent_x;
  dst.y += parent_y;
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0, 0xFF);
  // SDL_RenderRect(renderer, &dst);
  if (skin != NULL) {
    if (cache_is_outdated)
      update_cache(renderer);
    SDL_RenderTexture(renderer, cache, NULL, &dst);
  }
  for (GUIContainer *c : children)
    c->render(renderer, dst.x, dst.y);
}
