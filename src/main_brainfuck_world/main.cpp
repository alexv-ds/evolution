#include <bit>
#include <spdlog/spdlog.h>
#include "Agent.hpp"


int main() {
#ifdef SPDLOG_ACTIVE_LEVEL
  spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_ACTIVE_LEVEL));
#endif
  Agent::Memory memory = {
    .cells = std::vector<std::uint8_t>(10,'\0'),
    .program = [](){
      std::vector<ai::brainfuck::OpCode> program;
      const std::string_view str_program =
        ">+++++++++[<++++++++>-]<.>+++++++[<++++>-]<+.+"
        "++++++..+++.>>>++++++++[<++++>-]<.>>>+++++++++"
        "+[<+++++++++>-]<---.<<<<.+++.------.--------.>>"
        "+.>++++++++++.";
      program.reserve(str_program.size());
      for (const char ch : str_program) {
        program.push_back(std::bit_cast<ai::brainfuck::OpCode>(ch));
      }
      return program;
    }()
  };

  Agent::Callbacks callbacks = {
    .put = [](std::uint8_t cell){
      SPDLOG_INFO("PUT CALLBACK: {}", (char)cell);
      return true;
    },
    .read = [](std::uint8_t&) {
      SPDLOG_INFO("READ CALLBACK");
      return true;
    }
  };

  Agent agent(std::move(callbacks), std::move(memory));

  SPDLOG_INFO("Run agent");
  const std::size_t quota = agent.run(590);
  SPDLOG_INFO("Agent stoped. Remaining quota - {}", quota);
}
