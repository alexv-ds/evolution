file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/core/*.cpp")
file(GLOB_RECURSE CORE_HEADERS CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/core/*.hpp")

add_executable(tests-core
  ${CORE_SOURCES} ${CORE_HEADERS}
  core/core.helpers.field.cpp
  core/core.helpers.xy_iterator.cpp
)
target_link_libraries(tests-core PRIVATE Catch2::Catch2WithMain)
target_link_libraries(tests-core PRIVATE
  flecs::flecs_static
  sfml-graphics sfml-window
  spdlog::spdlog
)
target_include_directories(tests-core PRIVATE "${PROJECT_SOURCE_DIR}/src")
catch_discover_tests(tests-core)



