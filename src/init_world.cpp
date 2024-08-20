#include <thread>
#include <flecs.h>
#include <spdlog/spdlog.h>
#include "core/modules/map.hpp"

using namespace core::modules;
using namespace std::chrono_literals;

void init_world(flecs::world& world) {
  world.import<Map>();
  auto _ = world.scope("world");

  const map::MapSize map_size = {
    .x = 10000,
    .y = 1000
  };
  world.set(map_size);

//  world.entity().in

  for (std::int32_t x = 0; x < static_cast<std::int32_t>(map_size.x); ++x) {
    for (std::int32_t y = 0; y < static_cast<std::int32_t>(map_size.y); ++y) {
      world.entity()
        .set<map::Position>({x, y});
    }
  }

  world.import<core::modules::Map>();



}