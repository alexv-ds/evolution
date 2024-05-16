module;

#include <cstdint>
#include <vector>
#include <concepts>
#include <span>

export module core.helpers.field;

namespace core::helpers {

  export template<class ObjectT, std::unsigned_integral CoordT>
  class FieldLayer {
  public:
    using object_t [[maybe_unused]] = ObjectT;
    using coord_t [[maybe_unused]] = CoordT;

    const CoordT size_x;
    const CoordT size_y;

    inline FieldLayer(CoordT size_x, CoordT size_y);

    inline std::size_t xy_offset(CoordT x, CoordT y) noexcept;

    inline std::span<ObjectT> data() const noexcept;

  private:
    std::vector<ObjectT> field;

  };

//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////

  template<class ObjectT, std::unsigned_integral CoordT>
  inline std::size_t FieldLayer<ObjectT, CoordT>::xy_offset(const CoordT x, const CoordT y) noexcept {
    return 0;
  }

  template<class ObjectT, std::unsigned_integral CoordT>
  FieldLayer<ObjectT, CoordT>::FieldLayer(const CoordT size_x, const CoordT size_y)
    : field(size_x * size_y), size_x(size_x), size_y(size_y) {}

  template<class ObjectT, std::unsigned_integral CoordT>
  inline std::span<ObjectT> FieldLayer<ObjectT, CoordT>::data() const noexcept {
    return {this->field.data(), this->field.data() + this->field.size()};
  }


}