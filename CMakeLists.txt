cmake_minimum_required(VERSION 3.29.3 FATAL_ERROR)

project(evolution VERSION 0.0.1 LANGUAGES CXX)

if (PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed")
endif ()

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EVO_BUILD_TESTING ON CACHE BOOL "Build tests")

add_compile_definitions(
  SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE
  FLECS_CPP_NO_AUTO_REGISTRATION
)

add_compile_options(-march=native)

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
  URL "https://github.com/SanderMertens/flecs/archive/refs/tags/v4.0.1.tar.gz"
  URL_HASH "SHA3_256=a03a1a70d2697d1213574d1dae5f9fd4d8841919038e1e415e484e22b76385f9"
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
  VERSION sha-6d6e6054
  URL "https://github.com/SFML/SFML/archive/8f6a8316ad0964eb727226ceef9d7d3a6d6e6054.tar.gz"
  URL_HASH "SHA3_256=1f6d6867954e1a52e418c5ac8c8af3b78a2cf49f9c125f99312132a33231f096"
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
  URL "https://github.com/gabime/spdlog/archive/refs/tags/v1.14.1.tar.gz"
  URL_HASH "SHA3_256=2e0a254292faa1a1a97f198c10b43df454323e100c2802fb8abb4b7beba1b5f7"
  SYSTEM YES
  EXCLUDE_FROM_ALL YES
  OPTIONS
  "SPDLOG_ENABLE_PCH ON"
  "SPDLOG_USE_STD_FORMAT ON"
)
target_link_libraries(${PROJECT_NAME}_main PRIVATE spdlog::spdlog)

if (EVO_BUILD_TESTING)
  CPMAddPackage(
    NAME Catch2
    URL "https://github.com/catchorg/Catch2/archive/refs/tags/v3.7.0.tar.gz"
    URL_HASH "SHA3_256=897f9ab458ec5d3b6c7f5ba4aa50b6ab3a2a919f3c4c3b17f63fc7ce22533c42"
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