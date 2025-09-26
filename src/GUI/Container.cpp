#include <GUI/Container.hpp>

#include <iostream>
#include <stdexcept>

GUIContainer::GUIContainer() {}

GUIContainer::GUIContainer(std::optional<GUIUnit> width,
                           std::optional<GUIUnit> height,
                           std::optional<GUISegment> top,
                           std::optional<GUISegment> left,
                           std::optional<GUISegment> bottom,
                           std::optional<GUISegment> right)
    : width(width), height(height), top(top), left(left), bottom(bottom),
      right(right) {}

void GUIContainer::update(int parent_width, int parent_height) {
  int old_w = w, old_h = h;
  /* Width is set */
  if (width.has_value()) {
    w = width->to_pixels(parent_width);
    // std::cout << "w: " << w << std::endl;
    if (left.has_value()) {
      if (right.has_value())
        throw std::runtime_error("Redundant right value");
      x = left->calculate(parent_width, w);
      // std::cout << "x: " << x << std::endl;
    } else if (right.has_value()) {
      if (left.has_value())
        throw std::runtime_error("Redundant left value");
      int right_p = right->calculate(parent_width, w);
      x = parent_width - w - right_p;
      // std::cout << "Parent width: " << parent_width << std::endl;
      // std::cout << "Right: " << right_p << std::endl;
      // std::cout << "x: " << x << std::endl;
    } else {
      throw std::runtime_error(
          "Invalid horizontal sizing (left and right empty)");
    }
  } else /* Dynamic width */
  {
    if (!left.has_value() || !right.has_value())
      throw std::runtime_error(
          "Invalid horizontal sizing (left or right empty)");
    x = left->calculate(parent_width);
    // std::cout << "x " << x << std::endl;
    int right_p = right->calculate(parent_width);
    w = parent_width - x - right_p;
    // std::cout << "w " << w << std::endl;
  }

  /* Height is set */
  if (height.has_value()) {
    h = height->to_pixels(parent_height);
    if (top.has_value()) {
      if (bottom.has_value())
        throw std::runtime_error("Redundant bottom value");
      y = top->calculate(parent_height, h);
      // std::cout << "y: " << y << std::endl;
    } else if (bottom.has_value()) {
      if (top.has_value())
        throw std::runtime_error("Redundant top value");
      int bottom_p = bottom->calculate(parent_height, h);
      y = parent_height - h - bottom_p;
      // std::cout << "Bottom: " << bottom_p << std::endl;
      // std::cout << "y: " << y << std::endl;
    } else {
      throw std::runtime_error("Invalid vertical sizing");
    }
  } else /* Dynamic height */
  {
    if (!top.has_value() || !bottom.has_value())
      throw std::runtime_error("Invalid vertical sizing");
    y = top->calculate(parent_height);
    // std::cout << "y " << y << std::endl;
    int bottom_p = bottom->calculate(parent_height);
    h = parent_height - y - bottom_p;
    // std::cout << "h " << h << std::endl;
  }

  // std::cout << x << " " << y << " " << w << " " << h << std::endl;

  if (w != old_w || h != old_h)
    cache_is_outdated = true;

  for (GUIContainer *c : children)
    c->update(w, h);
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

SDL_FRect GUIContainer::get_bounding_rect() const {
  return {(float)x, (float)y, (float)w, (float)h};
}

int GUIContainer::get_width() const { return w; }
int GUIContainer::get_height() const { return h; }

/*
void GUIContainer::update(int parent_width, int parent_height) {
  int old_w = w, old_h = h;
  horizontal_sizing.calculate(parent_width, &x, &w);
  vertical_sizing.calculate(parent_height, &y, &h);
  int min_width_p = min_width.to_pixels(parent_width);
  int min_height_p = min_height.to_pixels(parent_height);
  if (w < min_width_p)
    w = min_width_p;
  if (h < min_height_p)
    h = min_height_p;
  if (w != old_w || h != old_h)
    cache_is_outdated = true;
  for (GUIContainer *c : children)
    c->update(w, h);
}
*/

void GUIContainer::add_container(GUIContainer *container) {
  children.push_back(container);
  children.back()->update(w, h);
}

void GUIContainer::update_cache(SDL_Renderer *renderer) {
  if (cache != NULL)
    SDL_DestroyTexture(cache);
  cache = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
                            SDL_TEXTUREACCESS_TARGET, w, h);
  SDL_SetRenderTarget(renderer, cache);
  skin->render({0, 0, (float)w, (float)h});
  SDL_SetRenderTarget(renderer, NULL);
  cache_is_outdated = false;
}

void GUIContainer::render(SDL_Renderer *renderer, int parent_x, int parent_y) {
  SDL_FRect dst = get_bounding_rect();

  // std::cout << dst.x << " " << dst.y << " " << dst.w << " " << dst.h <<
  // std::endl;

  if (!dst.w || !dst.h)
    return;
  dst.x += parent_x;
  dst.y += parent_y;
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0, 0xFF);
  SDL_RenderRect(renderer, &dst);
  if (skin != NULL) {
    if (cache_is_outdated)
      update_cache(renderer);
    SDL_RenderTexture(renderer, cache, NULL, &dst);
  }
  for (GUIContainer *c : children)
    c->render(renderer, dst.x, dst.y);
}
