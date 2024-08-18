#pragma once

#include <vector>
#include <concepts>
#include <span>
#include <stdexcept>
#include <limits>

namespace core::helpers {

  /**
   * A class that represents a fixed-size field in 2d space,
   * whose cells can be accessed by XY coordinates.
   *
   * @tparam ObjectT object type stored in cells
   * @tparam CoordT coordinate number type
   */
  template<class ObjectT, std::unsigned_integral CoordT>
  class FieldLayer {
  public:
    struct XY {
      CoordT x;
      CoordT y;
    };

    using object_t [[maybe_unused]] = ObjectT; ///< object type stored in cells
    using coord_t [[maybe_unused]] = CoordT; ///< coordinate number type

    /**
     * Default constructor. Creates invalid object (can be only copied/moved from another)
     */
    inline FieldLayer() = default;

    /**
     * Default copy constructor
     */
    FieldLayer(const FieldLayer&) = default;

    /**
     * Default copy operator
     * @param other
     * @return
     */
    FieldLayer& operator=(const FieldLayer& other) = default;

    /**
     * Move ctor
     */
    FieldLayer(FieldLayer&&) noexcept;

    /**
     * Move operator
     * @param other
     * @return
     */
    FieldLayer& operator=(FieldLayer&& other) noexcept;


    /**
     * Construct layer with given size
     * @param size_x
     * @param size_y
     * @throws std::exception
     */
    inline FieldLayer(CoordT size_x, CoordT size_y);

    /**
     * Get offset by XY coords
     * @param x x coordinate
     * @param y y coordinate
     * @return offset (always return 0, if object moved to another)
     */
    inline std::size_t xy_offset(CoordT x, CoordT y) const noexcept;

    /**
     * Get offset by X coordinate.
     * @param x x coordinate
     * @return offset (always return 0, if object moved to another)
     */
    inline std::size_t x_offset(CoordT x) const noexcept;

    /**
     * Get map data
     * @link xy_offset
     * @link x_offset
     * @return flat array
     */
    inline std::span<ObjectT> data();

    inline XY size() const noexcept;

  private:
    CoordT size_x = 0; ///< layer size x
    CoordT size_y = 0; ///< layer size y
    std::vector<ObjectT> field;
  };

  template<class ObjectT, std::unsigned_integral CoordT>
  FieldLayer<ObjectT, CoordT>& FieldLayer<ObjectT, CoordT>::operator=(FieldLayer&& other) noexcept {
    this->field = std::move(other.field);
    this->size_y = other.size_y;
    this->size_x = other.size_x;
    other.size_x = 0;
    other.size_y = 0;
    return *this;
  }

  template<class ObjectT, std::unsigned_integral CoordT>
  FieldLayer<ObjectT, CoordT>::FieldLayer(FieldLayer&& other) noexcept
    : field(std::move(other.field)), size_x(other.size_x), size_y(other.size_y) {
    other.size_x = 0;
    other.size_y = 0;
  }

  template<class ObjectT, std::unsigned_integral CoordT>
  inline FieldLayer<ObjectT, CoordT>::XY FieldLayer<ObjectT, CoordT>::size() const noexcept {
    return {
      .x = this->size_x,
      .y = this->size_y
    };
  }

  template<class ObjectT, std::unsigned_integral CoordT>
  FieldLayer<ObjectT, CoordT>::FieldLayer(const CoordT size_x, const CoordT size_y)
    : size_x(size_x), size_y(size_y) {
    if (size_x == 0 || size_y == 0) {
      throw std::logic_error("invalid constructor arguments");
    }
    if (size_x > std::numeric_limits<CoordT>::max() / size_y) {
      throw std::logic_error("multiply result of size_x and size_y larger than the type can hold");
    }
    this->field = std::vector<ObjectT>(size_x * size_y);
  }

  template<class ObjectT, std::unsigned_integral CoordT>
  inline std::size_t FieldLayer<ObjectT, CoordT>::xy_offset(const CoordT x, const CoordT y) const noexcept {
    return x * this->size_y + y;
  }

  template<class ObjectT, std::unsigned_integral CoordT>
  std::size_t FieldLayer<ObjectT, CoordT>::x_offset(CoordT x) const noexcept {
    return x * this->size_y;
  }

  template<class ObjectT, std::unsigned_integral CoordT>
  inline std::span<ObjectT> FieldLayer<ObjectT, CoordT>::data() {
    if (!this->field.size()) {
      throw std::logic_error("invalid FieldLayer state");
    }
    return {this->field.data(), this->field.size()};
  }
}

