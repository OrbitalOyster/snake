#ifndef GUI_LAYOUT_HPP_
#define GUI_LAYOUT_HPP_

#include <GUI/Segment.hpp>
#include <GUI/Unit.hpp>
#include <SDL3/SDL_rect.h>
#include <optional>

class GUILayout {
private:
  std::optional<GUIUnit> width = {}, height = {};
  std::optional<GUISegment> top = {}, left = {};
  std::optional<GUISegment> bottom = {}, right = {};

public:
  GUILayout(std::optional<GUIUnit> width, std::optional<GUIUnit> height,
            std::optional<GUISegment> top, std::optional<GUISegment> left,
            std::optional<GUISegment> bottom, std::optional<GUISegment> right);
  SDL_FRect calculate(float parent_width, float parent_height);
};

#endif
