#include <GUI/Skin.hpp>

Skin::Skin(Stretchable *base, std::optional<Stretchable> *hover,
           std::optional<Stretchable> *active)
    : base(base), hover(hover), active(active) {}

void Skin::render(SDL_FRect rect, std::optional<enum ContainerState> state) {
  if (!state.has_value())
    base->render(rect);
  else
    switch (state.value()) {
      case Hover:
        hover->has_value() ? hover->value().render(rect) : base->render(rect);
      break;
      case Active:
        active->has_value() ? active->value().render(rect) : base->render(rect);
      break;
    }
}
