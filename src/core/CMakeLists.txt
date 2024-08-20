add_library(evolution-core
  helpers/field.hpp
  helpers/xy_iterator.hpp
  modules/map.hpp
  modules/map.cpp
  helpers/time_measuring.hpp
)

add_library(evolution::core ALIAS evolution-core)

target_link_libraries(evolution-core PUBLIC
  flecs::flecs_static
  spdlog::spdlog
)

target_compile_options(evolution-core PRIVATE ${EVO_DEFAULT_TARGET_FLAGS})

target_include_directories(evolution-core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")