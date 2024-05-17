#include <cstdint>
#include <vector>
#include <format>
#include <concepts>
#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
import core.helpers.field;

using namespace core::helpers;

template <std::integral ObjectT, class CoordT>
static FieldLayer<ObjectT, CoordT> make_field(const CoordT size_x, const CoordT size_y) {
  FieldLayer<ObjectT, CoordT> field(size_x, size_y);
  ObjectT i = 0;
  for (ObjectT& obj : field.data()) {
    obj = ++i;
  }
  return field;
}

SCENARIO("FieldLayer correctly calculate offset") {
  GIVEN("constructed FieldLayer with size_x - 10, size_y - 20") {
    FieldLayer<int, std::uint32_t> field(10, 20);

    THEN("x_offset(0) returns 0") {
      REQUIRE(field.x_offset(0) == 0);
    }

    THEN("x_offset(1) returns 20") {
      REQUIRE(field.x_offset(1) == 20);
    }

    THEN("x_offset(2) returns 40") {
      REQUIRE(field.x_offset(2) == 40);
    }

    THEN("x_offset(9) returns 40") {
      REQUIRE(field.x_offset(9) == 180);
    }

    THEN("xy_offset(0,0) returns 0") {
      REQUIRE(field.xy_offset(0, 0) == 0);
    }

    THEN("xy_offset(0,1) returns 1") {
      REQUIRE(field.xy_offset(0, 1) == 1);
    }

    THEN("xy_offset(0,2) returns 2") {
      REQUIRE(field.xy_offset(0, 2) == 2);
    }

    THEN("xy_offset(0,19) returns 19") {
      REQUIRE(field.xy_offset(0, 19) == 19);
    }

    THEN("xy_offset(1,0) returns 20") {
      REQUIRE(field.xy_offset(1, 0) == 20);
    }

    THEN("xy_offset(1,1) returns 21") {
      REQUIRE(field.xy_offset(1, 1) == 21);
    }

    THEN("xy_offset(1,19) returns 39") {
      REQUIRE(field.xy_offset(1, 19) == 39);
    }

    THEN("xy_offset(9,0) returns 180") {
      REQUIRE(field.xy_offset(9, 0) == 180);
    }

    THEN("xy_offset(9,1) returns 181") {
      REQUIRE(field.xy_offset(9, 1) == 181);
    }

    THEN("xy_offset(9,19) returns 199") {
      REQUIRE(field.xy_offset(9, 19) == 199);
    }
  }
}

SCENARIO("FieldLayer throws on invalid size_x/y construct params") {
  using CoordT = std::uint16_t;
  struct XY {
    CoordT x;
    CoordT y;
  };

  const auto xy = GENERATE(
    XY{0, 0},
    XY{100, 0},
    XY{0, 100},
    XY{1000, 70} //multiply result is larger than std::uint16_t can hold (65536)
  );

  GIVEN(std::format("size_x - {}, size_y - {}", xy.x, xy.y)) {
    WHEN("FieldLayer constructs with size_x and size_y") {
      THEN("throws exception") {
        REQUIRE_THROWS([xy]() {
          return FieldLayer<int, CoordT>(xy.x, xy.y);
        }());
      }
    }
  }
}

SCENARIO("FieldLayer returns correctly data size") {
  struct Params {
    std::uint32_t x;
    std::uint32_t y;
    std::size_t data_size;
  };

  const auto params = GENERATE(
    Params{1, 2, 2},
    Params{1, 200, 200},
    Params{2, 200, 400},
    Params{200, 200, 40000},
    Params{255, 3, 765}
  );

  GIVEN(std::format("size_x - {}, size_y - {}", params.x, params.y)) {
    WHEN("FieldLayer constructs with size_x and size_y") {
      FieldLayer<int, std::uint32_t> field(params.x, params.y);
      THEN(std::format("FieldLayer::data() returns std::span with size = {}", params.data_size)) {
        REQUIRE(field.data().size() == params.data_size);
      }
    }
  }
}

SCENARIO("FieldLayer correctly copies") {
  GIVEN("FieldLayer with some data") {
    FieldLayer layer = make_field<unsigned, unsigned>(3,2);
    REQUIRE(layer.data().size() == 6);
    REQUIRE(layer.size().x == 3);
    REQUIRE(layer.size().y == 2);
    WHEN("Copy to other field (using copy constructor)") {
      FieldLayer other = layer;

      THEN("Both layers equal") {
        REQUIRE(other.data().size() == 6);
        REQUIRE(std::equal(layer.data().begin(), layer.data().end(), other.data().begin()));
        REQUIRE(other.size().x == layer.size().x);
        REQUIRE(other.size().y == layer.size().y);
      }
    }
    WHEN("Copy to other field (using copy operator)") {
      FieldLayer<unsigned, unsigned> other;
      REQUIRE(other.size().x == 0);
      REQUIRE(other.size().y == 0);
      other = layer;
      THEN("Both layers equal") {
        REQUIRE(other.data().size() == 6);
        REQUIRE(std::equal(layer.data().begin(), layer.data().end(), other.data().begin()));
        REQUIRE(other.size().x == layer.size().x);
        REQUIRE(other.size().y == layer.size().y);
      }
    }
  }
}

SCENARIO("FieldLayer::data() throws on invalid object") {
  GIVEN("Default constructed FieldLayer") {
    FieldLayer<unsigned, unsigned> layer;
    REQUIRE(layer.size().x == 0);
    REQUIRE(layer.size().y == 0);

    WHEN("Calls FiledLayer::data()") {
      THEN("Throw exception") {
        REQUIRE_THROWS(layer.data());
      }
    }
  }
}

SCENARIO("FieldLayer std::move() correctly moves") {
  GIVEN("FieldLayer with some data") {
    FieldLayer layer = make_field<unsigned, unsigned>(3,2);
    const std::vector<unsigned> to_check = {1,2,3,4,5,6};
    REQUIRE(layer.data().size() == 6);
    REQUIRE(std::equal(layer.data().begin(), layer.data().end(), to_check.begin()));
    WHEN("Move to other (using move constructor)") {
      FieldLayer<unsigned, unsigned> other = std::move(layer);
      
      THEN("layer.size().x is 0") {
        REQUIRE(layer.size().x == 0);
      }

      THEN("layer.size().y is 0") {
        REQUIRE(layer.size().y == 0);
      }

      THEN("layer.data() throws exception") {
        REQUIRE_THROWS(layer.data());
      }

      THEN("other.size().x is 3") {
        REQUIRE(other.size().x == 3);
      }

      THEN("other.size().y is 2") {
        REQUIRE(other.size().y == 2);
      }

      THEN("other.data() returns correctly data") {
        REQUIRE(other.data().size() == 6);
        REQUIRE(std::equal(other.data().begin(), other.data().end(), to_check.begin()));
      }
    }

    WHEN("Move to other (using move operator)") {
      FieldLayer<unsigned, unsigned> other;
      REQUIRE_THROWS(other.data());
      REQUIRE(other.size().x == 0);
      REQUIRE(other.size().y == 0);
      other = std::move(layer);

      THEN("layer.size().x is 0") {
        REQUIRE(layer.size().x == 0);
      }

      THEN("layer.size().y is 0") {
        REQUIRE(layer.size().y == 0);
      }

      THEN("layer.data() throws exception") {
        REQUIRE_THROWS(layer.data());
      }

      THEN("other.size().x is 3") {
        REQUIRE(other.size().x == 3);
      }

      THEN("other.size().y is 2") {
        REQUIRE(other.size().y == 2);
      }

      THEN("other.data() returns correctly data") {
        REQUIRE(other.data().size() == 6);
        REQUIRE(std::equal(other.data().begin(), other.data().end(), to_check.begin()));
      }
    }
  }
}