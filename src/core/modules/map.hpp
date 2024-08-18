#pragma once
#include <concepts>
#include <cstdint>
#include <type_traits>
#include <flecs.h>

namespace core::modules {

  namespace map {

    struct Position {
      std::int32_t x = 0;
      std::int32_t y = 0;
    };

    struct MapSize {
      std::uint32_t x = 0;
      std::uint32_t y = 0;
    };

    struct SanitizePositionSystem {};

    namespace phases {
      struct UpdateIndex {};
    }

    namespace _detail {

    }
  } // namespace map

  struct Map {
    explicit Map(flecs::world& world);
  };
} // namespace core::modules