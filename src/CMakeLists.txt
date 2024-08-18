add_executable(evolution
  main.cpp
  core/helpers/field.hpp
  core/helpers/xy_iterator.hpp
  core/modules/map.hpp
  core/modules/map.cpp
)

target_include_directories(evolution PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

target_compile_options(evolution PRIVATE
  -march=native
  -Wall
  -Wextra
  -pedantic
)

target_link_libraries(evolution PRIVATE
  flecs::flecs_static
  sfml-graphics sfml-window
  spdlog::spdlog
)
