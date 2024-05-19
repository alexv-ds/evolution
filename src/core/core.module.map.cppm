module;

#include <concepts>
#include <cstddef>
#include <flecs.h>

export module core.map;

import core.helpers.field;

namespace core::module {

  export struct Map {
    Map(flecs::world&);
  };

  namespace map {

    /**
     * Component
     */
    struct Position {
      std::int32_t x = 0;
      std::int32_t y = 0;
    };

    /**
     * Component
     * @tparam ObjectT
     */
    template<class ObjectT>
    class Index {
    public:
      using object_t = ObjectT;

      Index() = default;

      Index(const std::uint32_t size_x, std::uint32_t size_y)
        : field(size_x, size_y) {}

    private:
      core::helpers::FieldLayer<ObjectT, std::uint32_t> field;
    };

//    export template<class T, std::unsigned_integral CoordT>
//    flecs::entity create_index() {
//      return {};
//    }

  } // namespace map

} // namespace core::module




