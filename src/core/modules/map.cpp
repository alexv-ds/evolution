#include <algorithm>
#include "map.hpp"

using namespace core::modules::map;

namespace {
  struct SanitizePositionPhase {
  };

  void SanitizePosition(flecs::iter it) {
    while (it.next()) {
      const auto position = it.field<Position>(0);
      const auto map_size= it.field<const MapSize>(1);
      const auto size_x = static_cast<std::make_signed_t<decltype(map_size->x)>>(map_size->x);
      const auto size_y = static_cast<std::make_signed_t<decltype(map_size->y)>>(map_size->y);

      for (auto i: it) {
        if (position[i].x >= size_x) {
          position[i].x -= size_x;
        } else if (position[i].x < 0) {
          position[i].x += size_x;
        }

        if (position[i].y >= size_y) {
          position[i].y -= size_y;
        } else if (position[i].y < 0) {
          position[i].y += size_y;
        }

        position[i].x = std::clamp(position[i].x, 0, size_x - 1);
        position[i].y = std::clamp(position[i].y, 0, size_y - 1);
      }
    }
  }
}


namespace core::modules {
  Map::Map(flecs::world& world) {
    using namespace map;
    world.module<Map>("::core::map");

    // components
    {
      world.component<MapSize>()
        .member<decltype(MapSize::x)>("x")
        .member<decltype(MapSize::y)>("y");

      world.component<Position>()
        .member<decltype(Position::x)>("x")
        .member<decltype(Position::y)>("y");
    }

    // private components
    {
      world.component<MapSize>()
        .member<decltype(MapSize::x)>("x")
        .member<decltype(MapSize::y)>("y");
    }

    // phases
    {
      auto _ = world.scope("phases");

      world.entity<SanitizePositionPhase>()
        .add(flecs::Phase)
        .depends_on(flecs::PreUpdate);
      world.entity<phases::UpdateIndex>()
        .add(flecs::Phase)
        .depends_on<SanitizePositionPhase>();
    }

    // systems
    {
      auto _ = world.scope("systems");
      world.entity<SanitizePositionSystem>("SanitizePosition");
      world.system<Position, const MapSize>("SanitizePosition")
        .kind<SanitizePositionPhase>()
          //.instanced()
        .term_at(0).self()
        .term_at(1).singleton()
        .run(SanitizePosition);
    }


  }
} //namespace core::modules