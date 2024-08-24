#include <iostream>
#include <ai/brainfuck.hpp>
#include <spdlog/spdlog.h>


int main() {
#ifdef SPDLOG_ACTIVE_LEVEL
  spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_ACTIVE_LEVEL));
#endif

  std::string out;
  out.reserve(200);

  std::vector<std::uint8_t> cells(10, 0);
  const std::string_view program =
    ">+++++++++[<++++++++>-]<.>+++++++[<++++>-]<+.+"
    "++++++..+++.>>>++++++++[<++++>-]<.>>>+++++++++"
    "+[<+++++++++>-]<---.<<<<.+++.------.--------.>>"
    "+.>++++++++++.";

  ai::brainfuck::VM vm(
    {
      .cells = {cells.data(), cells.size()},
      .program = {reinterpret_cast<const ai::brainfuck::OpCode*>(program.data()), program.size()},
      .program_counter = 0,
      .cell_counter = 0
    }
  );

  ai::brainfuck::SuspendReason suspend_reason = {
    .quota = 490
  };

  SPDLOG_INFO("VM start");
  do {
    suspend_reason = vm.run(suspend_reason.quota);
    if (auto* put = std::get_if<ai::brainfuck::PutAction>(&suspend_reason.action); put != nullptr) {
      out.push_back(static_cast<char>(*put->cell));
    }
  } while(suspend_reason.quota != 0);
  SPDLOG_INFO("Execution result: '{}'", out);
}
