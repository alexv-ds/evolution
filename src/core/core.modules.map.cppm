module;
#include <concepts>
#include <cstdint>
#include <type_traits>
#include <flecs.h>
#include <spdlog/spdlog.h>
export module core.modules.map;

import core.helpers.field;

namespace core::modules {

  namespace map {

    export struct Position {
      std::int32_t x = 0;
      std::int32_t y = 0;
    };

    export struct MapSize {
      std::uint32_t x = 0;
      std::uint32_t y = 0;
    };

    export struct SanitizePositionSystem {};

    namespace phases {
      export struct UpdateIndex {};
    }

    namespace _detail {
      struct SanitizePositionPhase {};


      static void SanitizePosition(flecs::iter it,
                                   Position* pos /* self */,
                                   const MapSize* map_size /* singleton */) {
        const auto size_x = static_cast<std::make_signed_t<decltype(map_size->x)>>(map_size->x);
        const auto size_y = static_cast<std::make_signed_t<decltype(map_size->y)>>(map_size->y);

        for (auto i : it) {
          pos[i].x = pos[i].x % size_x;
          pos[i].x = pos[i].y % size_y;
        }
      }

    }

  } // namespace map

  export struct Map {
    explicit Map(flecs::world& world) {
      using namespace map;
      world.module<Map>("::core::map");

      // region Components
      {
        world.component<MapSize>()
          .member<decltype(MapSize::x)>("x")
          .member<decltype(MapSize::y)>("y");

        world.component<Position>()
          .member<decltype(Position::x)>("x")
          .member<decltype(Position::y)>("y");
      }
      // endregion

      // region Private Components
      {
        world.component<MapSize>()
          .member<decltype(MapSize::x)>("x")
          .member<decltype(MapSize::y)>("y");
      }
      // endregion

      // region Phases
      {
        auto _ = world.scope("phases");

        world.entity<_detail::SanitizePositionPhase>()
          .add(flecs::Phase)
          .depends_on(flecs::PreUpdate);

        world.entity<phases::UpdateIndex>()
          .add(flecs::Phase)
          .depends_on<_detail::SanitizePositionPhase>();
      }
      // endregion

      // region Systems
      {
//        auto _ = world.scope("systems");
//        world.entity<SanitizePositionSystem>("SanitizePosition");
//        world.system<Position, MapSize>("SanitizePosition")
//          .kind<_detail::SanitizePositionPhase>()
//          .instanced()
//          .arg(1).self()
//          .arg(2).singleton()
//          .iter(_detail::SanitizePosition);
      }
      // endregion
    }
  };
} // namespace core::module




