#include <string_view>
#include <array>
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <ai/brainfuck.hpp>

SCENARIO("Brainfuck VM - 'Hello World' program") {
  GIVEN("VM with 'Hello World' program") {
    std::array<std::uint8_t, 10> cells = {};
    std::fill(cells.begin(), cells.end(), '\0');
    const std::string_view program =
      ">+++++++++[<++++++++>-]<.>+++++++[<++++>-]<+.+"
      "++++++..+++.>>>++++++++[<++++>-]<.>>>+++++++++"
      "+[<+++++++++>-]<---.<<<<.+++.------.--------.>>"
      "+.>++++++++++.";

    ai::brainfuck::VM vm(
      {
        .cells = {cells.data(), cells.size()},
        .program = {reinterpret_cast<const ai::brainfuck::OpCode*>(program.data()), program.size()}
      }
    );

    WHEN("VM run with 490 quota") {
      std::string out;

      ai::brainfuck::SuspendReason suspend_reason = {
        .quota = 490
      };
      do {
        suspend_reason = vm.run(suspend_reason.quota);
        REQUIRE(std::get_if<ai::brainfuck::ReadAction>(&suspend_reason.action) == nullptr);
        if (auto* put = std::get_if<ai::brainfuck::PutAction>(&suspend_reason.action); put != nullptr) {
          out.push_back(static_cast<char>(*put->cell));
        }
      } while (suspend_reason.quota != 0);

      THEN("result string - 'Hello World!'") {
        REQUIRE(out == "Hello World!");
      }
    }


  }
}

TEST_CASE("VM 'Hello World' benchmark", "[!benchmark]") {

  std::array<std::uint8_t, 10> cells = {};
  std::fill(cells.begin(), cells.end(), '\0');
  const std::string_view program =
    ">+++++++++[<++++++++>-]<.>+++++++[<++++>-]<+.+"
    "++++++..+++.>>>++++++++[<++++>-]<.>>>+++++++++"
    "+[<+++++++++>-]<---.<<<<.+++.------.--------.>>"
    "+.>++++++++++.";

  ai::brainfuck::VM vm(
    {
      .cells = {cells.data(), cells.size()},
      .program = {reinterpret_cast<const ai::brainfuck::OpCode*>(program.data()), program.size()}
    }
  );

  // @formatter:off
  BENCHMARK("VM run with 490 quota") {
    ai::brainfuck::SuspendReason suspend_reason = {
      .quota = 490
    };
    std::string out;
    do {
      suspend_reason = vm.run(suspend_reason.quota);
      if (auto* put = std::get_if<ai::brainfuck::PutAction>(&suspend_reason.action); put != nullptr) {
        out.push_back(static_cast<char>(*put->cell));
      }
    } while (suspend_reason.quota != 0);

    return out;
  };
  // @formatter:on
}
