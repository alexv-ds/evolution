cmake_minimum_required(VERSION 3.29.3 FATAL_ERROR)

project(evolution VERSION 0.0.1 LANGUAGES CXX)


if (PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed")
endif ()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EVO_BUILD_TESTING OFF CACHE BOOL "Build tests")

add_compile_definitions(
  SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE
  FLECS_CPP_NO_AUTO_REGISTRATION
)

add_executable(${PROJECT_NAME}
  src/main.cpp
)

add_library(${PROJECT_NAME}_main STATIC)
target_sources(${PROJECT_NAME}_main PUBLIC FILE_SET CXX_MODULES FILES
  src/main.cppm
  src/core/core.modules.map.cppm
  src/core/core.helpers.field.cppm
  src/core/core.helpers.xy_iterator.cppm
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

if (EVO_BUILD_TESTING)
  CPMAddPackage(
    NAME Catch2
    URL "https://github.com/catchorg/Catch2/archive/refs/tags/v3.5.4.tar.gz"
    URL_HASH "SHA3_256=6908501ace10bca5ece01a972e4834777f3b3cb5e14b391cec015caeb5470eff"
    OPTIONS
    "CATCH_INSTALL_DOCS OFF"
    "CATCH_INSTALL_EXTRAS OFF"
    "CATCH_ENABLE_REPRODUCIBLE_BUILD OFF"
  )
  list(APPEND CMAKE_MODULE_PATH "${Catch2_SOURCE_DIR}/extras")

  include(CTest)
  include(Catch)
  enable_testing()

  add_subdirectory(test)
endif ()