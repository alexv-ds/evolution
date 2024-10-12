CPMAddPackage(
  NAME flecs
  URL "https://github.com/SanderMertens/flecs/archive/refs/tags/v4.0.2.tar.gz"
  SYSTEM YES
  EXCLUDE_FROM_ALL YES
  OPTIONS
  "FLECS_STATIC ON"
  "FLECS_SHARED OFF"
  "FLECS_PIC OFF"
  "FLECS_TESTS OFF"
)

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

CPMAddPackage(
  NAME Boost
  VERSION 1.86.0.beta1
  URL "https://github.com/boostorg/boost/releases/download/boost-1.86.0.beta1/boost-1.86.0.beta1-cmake.tar.xz"
  URL_HASH "SHA3_256=8727798bb5c7efd243e6b23432299cd999bfe8d291c0dd5a52ef4c569bcdecbd"
  SYSTEM YES
  EXCLUDE_FROM_ALL YES
  OPTIONS
  "BOOST_ENABLE_CMAKE ON"
)

CPMAddPackage(
  NAME Boost
  VERSION 1.86.0.beta1
  URL "https://github.com/boostorg/boost/releases/download/boost-1.86.0.beta1/boost-1.86.0.beta1-cmake.tar.xz"
  URL_HASH "SHA3_256=8727798bb5c7efd243e6b23432299cd999bfe8d291c0dd5a52ef4c569bcdecbd"
  SYSTEM YES
  EXCLUDE_FROM_ALL YES
  OPTIONS
  "BOOST_ENABLE_CMAKE ON"
)
add_compile_definitions(BOOST_ASIO_NO_DEPRECATED)

CPMAddPackage("gh:alexv-ds/cpp-fast-pimpl@2.0.1")

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
endif ()
