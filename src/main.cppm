module;
#include <spdlog/spdlog.h>
#include <flecs.h>

export module main;

export int cxx_main(int argc, char* argv[]) {
#ifdef SPDLOG_ACTIVE_LEVEL
  spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_ACTIVE_LEVEL));
#endif
  SPDLOG_TRACE("HI DUDDLES");
  return 0;
}