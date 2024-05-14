cmake_minimum_required(VERSION 3.29.3 FATAL_ERROR)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")


project(evolution VERSION 0.0.1 LANGUAGES CXX)


if (PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed")
endif ()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED 23)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_definitions(
  SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE
)

add_executable(${PROJECT_NAME}
  src/main.cpp
)

add_library(${PROJECT_NAME}_main STATIC)
target_sources(${PROJECT_NAME}_main PUBLIC FILE_SET CXX_MODULES FILES
  src/main.cppm
  src/core/core.map.cppm
)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_main)

###########################################################

include(cmake/get_cpm.cmake)

CPMAddPackage(
  NAME flecs
  URL "https://github.com/SanderMertens/flecs/archive/5b65eb378eda9330d530b1a3f4de556f0819c0b2.tar.gz"
  URL_HASH "SHA3_256=2d81c326084d66bbb07a24421b0b28602afdf2106e7bd34cb8fdf061174e2d98"
  SYSTEM YES
  EXCLUDE_FROM_ALL YES
  OPTIONS
  "FLECS_STATIC ON"
  "FLECS_SHARED OFF"
  "FLECS_PIC OFF"
  "FLECS_TESTS OFF"
)
target_link_libraries(${PROJECT_NAME}_main PRIVATE flecs::flecs_static)

CPMAddPackage(
  NAME SFML
  URL "https://github.com/SFML/SFML/archive/b79d5553fd9dd174deab7d6f4f05fe7e16178eab.tar.gz"
  URL_HASH "SHA3_256=f2e7e9e1d004a4663eb30fdadca6b4e58e6e5380495d348b48d035e6401ea7f4"
  SYSTEM YES
  EXCLUDE_FROM_ALL YES
  OPTIONS
  "SFML_BUILD_WINDOW ON"
  "SFML_BUILD_GRAPHICS ON"
  "SFML_BUILD_AUDIO OFF"
  "SFML_BUILD_NETWORK OFF"
)
target_link_libraries(${PROJECT_NAME}_main PRIVATE sfml-graphics sfml-window)

CPMAddPackage(
  NAME spdlog
  URL "https://github.com/gabime/spdlog/archive/refs/tags/v1.13.0.tar.gz"
  URL_HASH "SHA3_256=5207d1b63e3c1466d30b3e28a0d7accfccad6eca283df8c04999dde9fdf3de68"
  OPTIONS
  "SPDLOG_ENABLE_PCH ON"
  "SPDLOG_USE_STD_FORMAT ON"
)
target_link_libraries(${PROJECT_NAME}_main PRIVATE spdlog::spdlog)
