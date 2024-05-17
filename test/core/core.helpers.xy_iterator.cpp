#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <algorithm>
import core.helpers.xy_iterator;

using namespace core::helpers;

SCENARIO("xy struct compares correctly") {
  GIVEN("two equal xy structs") {
    xy<int> xy1 = {3, -5};
    xy<int> xy2 = {3, -5};

    REQUIRE(xy1 == xy2);
    REQUIRE_FALSE(xy1 != xy2);
  }

  GIVEN("two non equal xy structs") {
    xy<int> xy1 = {3, -5};
    xy<int> xy2 = {6, -2};

    REQUIRE_FALSE(xy1 == xy2);
    REQUIRE(xy1 != xy2);
  }
}

SCENARIO("xy_iterator default construct with zero xy") {
  GIVEN("default constructed xy_iterator") {
    xy_iterator<int> it;
    REQUIRE(it->x == 0);
    REQUIRE(it->y == 0);
  }
}

SCENARIO("xy_iterator operator*() returns correct data") {
  GIVEN("{4,5} {6,6} constructed xy_iterator") {
    xy_iterator<int> it({4,5}, {6,6});
    xy<int> xy = *it;
    REQUIRE(xy.x == 4);
    REQUIRE(xy.y == 5);
  }
}

SCENARIO("xy_iterator operator->() returns correct data") {
  GIVEN("{4,5} {6,6} constructed xy_iterator") {
    xy_iterator<int> it({4,5}, {6,6});
    REQUIRE(it->x == 4);
    REQUIRE(it->y == 5);
  }
}

SCENARIO("xy_iterator correctly iterates") {
  GIVEN("{1,1} {2,2} constructed xy_iterator") {
    xy_iterator<int> it({1,1}, {2,2});
    REQUIRE(it->x == 1);
    REQUIRE(it->y == 1);

    WHEN("++it one times") {
      ++it;
      THEN("returns {1,2}") {
        REQUIRE(it->x == 1);
        REQUIRE(it->y == 2);
      }
    }

    WHEN("++it two times") {
      ++it;
      ++it;
      THEN("returns {2,1}") {
        REQUIRE(it->x == 2);
        REQUIRE(it->y == 1);
      }
    }

    WHEN("std::distance() by it") {
      auto dist = std::distance(it.begin(), it.end());
      THEN("distance is 4") {
        REQUIRE(dist == 4);
      }
      THEN("current xy is - {1,1}") {
        REQUIRE(it->x == 1);
        REQUIRE(it->y == 1);
      }
    }

    WHEN("iterate from begin to end") {
      REQUIRE(std::distance(it.begin(), it.end()) == 4);
      THEN("it range qual range of ({1,1}, {1,2}, {2,1}, {2,2})") {
        std::vector<xy<int>> to_check = {
          {1,1}, {1,2}, {2,1}, {2,2}
        };
        REQUIRE(std::ranges::equal(it, to_check) == true);
      }
    }
  }
}