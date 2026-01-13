#include <GUI/Skin.hpp>

Skin::Skin(Stretchable *base, Stretchable *hover, Stretchable *active)
    : base(base), hover(hover), active(active) {}

void Skin::render(SDL_FRect rect, enum ContainerState state) {
  switch (state) {
  case Base:
    base->render(rect);
    break;
  case Hover:
    hover ? hover->render(rect) : base->render(rect);
    break;
  case Active:
    active ? active->render(rect) : base->render(rect);
    break;
  }
}
