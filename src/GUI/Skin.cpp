#include <GUI/Skin.hpp>

Skin::Skin(Stretchable *base, std::optional<Stretchable *> hover,
           std::optional<Stretchable *> active)
    : base(base) {
  if (hover.has_value())
    this->hover = hover.value();
  if (active.has_value())
    this->active = active.value();
}

void Skin::render(SDL_FRect rect, std::optional<enum ContainerState> state) {
  if (!state.has_value())
    base->render(rect);
  else
    switch (state.value()) {
    case Hover:
      hover ? hover->render(rect) : base->render(rect);
      break;
    case Active:
      active ? active->render(rect) : base->render(rect);
      break;
    }
}
