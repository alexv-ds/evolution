module;
#include <spdlog/spdlog.h>
#include <flecs.h>

export module main;
import core.helpers.field;


using namespace core::helpers;


export int cxx_main(int argc, char* argv[]) {
#ifdef SPDLOG_ACTIVE_LEVEL
  spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_ACTIVE_LEVEL));
#endif
  SPDLOG_TRACE("Hello world!");

  FieldLayer<int, unsigned> layer(255, 255);


  return 0;
}