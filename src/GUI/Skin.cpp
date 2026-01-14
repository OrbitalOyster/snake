#include <GUI/Skin.hpp>

Skin::Skin(Stretchable *base, Stretchable *hover, Stretchable *active)
    : base(base), hover(hover), active(active) {}

void Skin::render(SDL_FRect *dst, enum ContainerState state) {
  switch (state) {
  case Base:
    base->render(dst);
    break;
  case Hover:
    hover ? hover->render(dst) : base->render(dst);
    break;
  case Active:
    active ? active->render(dst) : base->render(dst);
    break;
  }
}
