add_library(evolution-core
  helpers/field.hpp
  helpers/xy_iterator.hpp
  modules/map.hpp
  modules/map.cpp
  helpers/time_measuring.hpp
  Core.cpp
  Core.hpp
  modules/visualization.cpp
  modules/visualization.hpp
  modules/io.cpp
  modules/io.hpp
  modules/visualization/impl/components.hpp
)

add_library(evolution::core ALIAS evolution-core)

target_link_libraries(evolution-core PUBLIC
  flecs::flecs_static
  spdlog::spdlog
  sfml-graphics
  Boost::core
  Boost::dll
  Boost::asio
)

target_compile_options(evolution-core PRIVATE ${EVO_DEFAULT_TARGET_FLAGS})

target_include_directories(evolution-core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")
