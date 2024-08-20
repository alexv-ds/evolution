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
      const auto size_x = static_cast<decltype(position->x)>(map_size->x);
      const auto size_y = static_cast<decltype(position->y)>(map_size->y);

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

  void SanitizePosition2(flecs::iter it) {
    while (it.next()) {
      const auto position = it.field<Position>(0);
      const auto map_size= it.field<const MapSize>(1);
      const auto size_x = static_cast<decltype(position->x)>(map_size->x);
      const auto size_y = static_cast<decltype(position->y)>(map_size->y);

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
      }
    }
  }

  void SanitizePosition3(flecs::iter it) {
    while (it.next()) {
      const auto position = it.field<Position>(0);
      const auto map_size= it.field<const MapSize>(1);
      const auto size_x = static_cast<decltype(position->x)>(map_size->x);
      const auto size_y = static_cast<decltype(position->y)>(map_size->y);

      for (auto i: it) {
        position[i].x = position[i].x % size_x;
        position[i].y = position[i].y % size_y;

        if (position[i].x < 0) {
          position[i].x = size_x - position[i].x;
        }

        if (position[i].y < 0) {
          position[i].y = size_x - position[i].y;
        }
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

      world.component<Layer>();
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

      world.system<Position, const MapSize>("SanitizePosition_V2")
        .kind<SanitizePositionPhase>()
          //.instanced()
        .term_at(0).self()
        .term_at(1).singleton()
        .run(SanitizePosition2);

      world.system<Position, const MapSize>("SanitizePosition_V3")
        .kind<SanitizePositionPhase>()
          //.instanced()
        .term_at(0).self()
        .term_at(1).singleton()
        .run(SanitizePosition3);
    }


  }
} //namespace core::modules