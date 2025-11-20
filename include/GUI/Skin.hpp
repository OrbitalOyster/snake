#ifndef GUI_SKIN_HPP_
#define GUI_SKIN_HPP_

#include <Stretchable.hpp>
#include <optional>

enum ContainerState { Base, Hover, Active };

class Skin {
private:
  Stretchable *base;
  Stretchable *hover = NULL;
  Stretchable *active = NULL;

public:
  Skin(Stretchable *base, std::optional<Stretchable *> hover,
       std::optional<Stretchable *> active);
  void render(SDL_FRect rect, enum ContainerState state = Base);
};

#endif
