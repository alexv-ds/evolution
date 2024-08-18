cmake_minimum_required(VERSION 3.30.2 FATAL_ERROR)

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

include(cmake/get_cpm.cmake)
include(cmake/cpm-dependencies.cmake)

add_subdirectory(src)

if (EVO_BUILD_TESTING)
  include(CTest)
  include(Catch)
  enable_testing()
  add_subdirectory(test)
endif ()