# main
cmake_minimum_required(VERSION 3.10)
project(snake LANGUAGES CXX)
add_executable(main)

target_sources(main PRIVATE
    src/main.cpp
    src/Config.cpp
    src/Core.cpp
    src/Font.cpp
)

include_directories(include)

# Create output directory
file(MAKE_DIRECTORY build)

# yaml-cpp
include(FetchContent)
FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG master
)
FetchContent_MakeAvailable(yaml-cpp)
include_directories(${PROJECT_SOURCE_DIR}/yaml-cpp/include)

# SDL
add_subdirectory(SDL EXCLUDE_FROM_ALL)
include_directories(${PROJECT_SOURCE_DIR}/SDL/include)

# SDL_image
add_subdirectory(SDL_image EXCLUDE_FROM_ALL)

# SDL_ttf
set(SDLTTF_VENDORED ON)
add_subdirectory(SDL_ttf EXCLUDE_FROM_ALL)

# Link all external libraries
target_link_libraries(main PRIVATE yaml-cpp::yaml-cpp  SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf)
