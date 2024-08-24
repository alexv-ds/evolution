file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/core/*.cpp")
file(GLOB_RECURSE CORE_HEADERS CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/core/*.hpp")

add_executable(tests-core
  core.helpers.field.cpp
  core.helpers.xy_iterator.cpp
)
target_link_libraries(tests-core PRIVATE Catch2::Catch2WithMain evolution::core)
catch_discover_tests(tests-core)



