#ifndef GUI_SKIN_HPP_
#define GUI_SKIN_HPP_

#include <Stretchable.hpp>
#include <optional>

enum ContainerState { Hover, Active };

class Skin {
private:
  Stretchable *base;
  std::optional<Stretchable> *hover;
  std::optional<Stretchable> *active;

public:
  Skin(Stretchable *base, std::optional<Stretchable> *hover,
       std::optional<Stretchable> *active);
  void render(SDL_FRect rect, std::optional<enum ContainerState> state);
};

#endif
