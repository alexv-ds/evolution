

add_executable(tests-core
  core/core.helpers.field.cpp
  core/core.helpers.xy_iterator.cpp
)
target_link_libraries(tests-core PRIVATE Catch2::Catch2WithMain ${PROJECT_NAME}_main)
catch_discover_tests(tests-core)