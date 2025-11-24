#ifndef GUI_LAYOUT_HPP_
#define GUI_LAYOUT_HPP_

#include <GUI/Segment.hpp>
#include <GUI/Unit.hpp>
#include <SDL3/SDL_rect.h>
#include <optional>

class GUILayout {
private:
  std::optional<GUIUnit> width = {}, height = {};
  std::optional<GUISegment> left = {}, top = {}, right = {}, bottom = {};

public:
  GUILayout(std::optional<GUIUnit> width, std::optional<GUIUnit> height,
            std::optional<GUISegment> left, std::optional<GUISegment> top,
            std::optional<GUISegment> right, std::optional<GUISegment> bottom);
  GUILayout();
  GUILayout(GUIUnit width, GUIUnit height, GUISegment left, GUISegment top);
  GUILayout(GUISegment left, GUISegment top, GUISegment right, GUISegment bottom);
  void move();
  SDL_FRect calculate(float parent_width, float parent_height);
};

#endif
