#ifndef GUI_CONTAINER_HPP_
#define GUI_CONTAINER_HPP_

#include <GUI/Alignment.hpp>
#include <GUI/Segment.hpp>
#include <GUI/Sizing.hpp>
#include <GUI/Skin.hpp>
#include <GUI/Unit.hpp>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <optional>
#include <vector>

class GUIContainer {
private:
  /* Alignment chicanery */
  // GUIAlignment horizontal_alignment, vertical_alignment;

  std::optional<GUIUnit> width = GUIUnit(1.0f), height = GUIUnit(1.0f);
  std::optional<GUISegment> top, left;
  std::optional<GUISegment> bottom, right;

  GUISizing horizontal_sizing, vertical_sizing;
  /* Actual dimensions */
  int x, y;
  int w, h;
  GUIUnit min_width, min_height;
  /* Cache, updating on resize */
  SDL_Texture *cache = NULL;
  bool cache_is_outdated = false;
  GUISkin *skin = NULL;
  std::vector<GUIContainer *> children;

public:
  GUIContainer();

  GUIContainer(std::optional<GUIUnit> width, std::optional<GUIUnit> height,
               std::optional<GUISegment> top, std::optional<GUISegment> left,
               std::optional<GUISegment> bottom = {}, std::optional<GUISegment> right = {});

  GUIContainer(GUISizing horizontal_sizing, GUISizing vertical_sizing);
  void set_skin(GUISkin *skin);
  void set_min_width(GUIUnit min_width);
  void set_min_height(GUIUnit min_height);
  SDL_FRect get_bounding_rect() const;
  int get_width() const;
  int get_height() const;
  // void update(int parent_width, int parent_height);
  void update(int parent_width, int parent_height);
  void resize(int new_width, int new_height);
  void on_parent_resize(int new_parent_width, int new_parent_height);
  void add_container(GUIContainer *container);
  void update_cache(SDL_Renderer *renderer);
  void render(SDL_Renderer *renderer, int parent_x, int parent_y);
};

#endif
