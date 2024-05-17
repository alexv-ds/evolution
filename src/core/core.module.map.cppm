module;

#include <concepts>
#include <flecs.h>

export module core.map;

namespace core::module {

  export struct Map {
    Map(flecs::world&);
  };

  namespace map {

    template<class T, std::unsigned_integral CoordT>
    class Index {
    public:
      Index(CoordT size_x, CoordT size_y) {

      }
    private:
    };

//    export template<class T, std::unsigned_integral CoordT>
//    flecs::entity create_index() {
//      return {};
//    }

  } // namespace map

} // namespace core::module




