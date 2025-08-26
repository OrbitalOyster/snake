# main
cmake_minimum_required(VERSION 3.10)
project(snake LANGUAGES CXX)
add_executable(main main.cpp)

include_directories(${PROJECT_SOURCE_DIR}/yaml-cpp/include)

# yaml-cpp

include(FetchContent)

FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG master
)
FetchContent_MakeAvailable(yaml-cpp)

target_link_libraries(main yaml-cpp::yaml-cpp)
