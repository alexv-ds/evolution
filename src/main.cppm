module;

#include <spdlog/spdlog.h>
#include <flecs.h>

export module main_enty;

import core.helpers.field;
import core.modules.map;

using namespace core::helpers;

using namespace core::modules;

export int cxx_main(int argc, char* argv[]) {
#ifdef SPDLOG_ACTIVE_LEVEL
  spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_ACTIVE_LEVEL));
#endif
  SPDLOG_TRACE("Hello world!");

  flecs::world world;
  world.import<Map>();
  world.set<map::MapSize>({100, 100});

  {
    auto _ = world.scope("world");
    for (int x = 0; x <= 100; ++x) {
      for (int y = 0; y <= 100; ++y) {
        world.entity()
          .set<map::Position>({x, y});
      }
    }
  }


  return world.app()
    .target_fps(60)
    .enable_rest()
    .enable_stats()
    .threads(8)
    .run();
}