#include <spdlog/spdlog.h>
#include <flecs.h>

#include "core/helpers/field.hpp"
#include "core/modules/map.hpp"

using namespace core::helpers;
using namespace core::modules;

int main(int argc, char* argv[]) {
#ifdef SPDLOG_ACTIVE_LEVEL
  spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_ACTIVE_LEVEL));
#endif
  flecs::world world;
  world.import<core::modules::Map>();
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
  SPDLOG_TRACE("World run");
  return world.app()
    .target_fps(60)
    .enable_rest()
    .enable_stats()
    .threads(8)
    .run();
}