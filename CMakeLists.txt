cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

project(evolution VERSION 0.0.1 LANGUAGES CXX)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed")
endif()

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EVO_BUILD_TESTING OFF CACHE BOOL "Build tests")

set(EVO_DEFAULT_TARGET_FLAGS
  $<$<NOT:$<CONFIG:Debug>>:-march=native>
  -Wall
  -Wextra
  -pedantic
)

add_compile_definitions(
  SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE
  FLECS_CPP_NO_AUTO_REGISTRATION
)

include(cmake/get_cpm.cmake)
include(cmake/cpm-dependencies.cmake)

#find_program(EVO_CPPCHECK NAMES cppcheck)
#if(EVO_CPPCHECK)
#  set(CMAKE_CXX_CPPCHECK "${EVO_CPPCHECK}")
#  list(APPEND CMAKE_CXX_CPPCHECK
#    "--enable=all"
#    "--force"
#    "--suppress=missingIncludeSystem"
#  )
#endif()

add_subdirectory(src)

if(EVO_BUILD_TESTING)
  include(CTest)
  include(Catch)
  enable_testing()
  add_subdirectory(test)
endif()

