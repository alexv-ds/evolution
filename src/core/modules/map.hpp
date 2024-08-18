#pragma once
#include <concepts>
#include <cstdint>
#include <type_traits>
#include <flecs.h>
#include <core/helpers/field.hpp>

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

    // relations with layer
    struct Layer {};

    struct SanitizePositionSystem {};

    namespace phases {
      struct UpdateIndex {};
    }
  } // namespace map

  class Map {
    using field_layer_t = helpers::FieldLayer<flecs::entity_t, std::uint32_t>;
  public:
    using XY = field_layer_t::XY;

    [[nodiscard]] XY size() const noexcept {
      return this->field.size();
    };

//    void resize();

    explicit Map(flecs::world& world);
  private:
    field_layer_t field;
  };
} // namespace core::modules