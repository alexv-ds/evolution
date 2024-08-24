#pragma once

#include <span>
#include <cstdint>
#include <variant>

namespace ai::brainfuck {

  enum class OpCode : char {
    NEXT_CELL = '>',
    PREV_CELL = '<',
    INCREMENT = '+',
    DECREMENT = '-',
    PUT = '.',
    READ = ',',
    OPEN_BRACKET = '[',
    CLOSE_BRACKET = ']'
  };

  struct Context {
    std::span<std::uint8_t> cells;
    std::span<const OpCode> program;
    std::size_t program_counter = 0;
    std::size_t cell_counter = 0;
  };


} // namespace ai::brainfuck
