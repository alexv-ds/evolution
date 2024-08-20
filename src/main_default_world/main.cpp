#include <spdlog/spdlog.h>
#include <flecs.h>
#include <core/helpers/time_measuring.hpp>

using namespace core;

void init_world(flecs::world & );

int main() {
#ifdef SPDLOG_ACTIVE_LEVEL
  spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_ACTIVE_LEVEL));
#endif
  flecs::world world;

  {
    const helpers::TimeMeasuring init_measure;
    init_world(world);
    const auto duration = init_measure.measure<std::chrono::duration<float>>();
    SPDLOG_INFO("World initialised - {0:.2f}s", duration.count());
  }


  SPDLOG_TRACE("World run");
  return world.app()
    .target_fps(60)
    .enable_rest()
    .enable_stats()
    .threads(8)
    .run();
}