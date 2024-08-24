#pragma once

#include <vector>
#include <span>
#include <functional>
#include <boost/noncopyable.hpp>
#include <ai/brainfuck.hpp>

class Agent : public boost::noncopyable {
public:
  struct Callbacks {
    std::function<bool(std::uint8_t)> put;
    std::function<bool(std::uint8_t&)> read;
  };

  struct Memory {
    std::vector<std::uint8_t> cells;
    std::vector<ai::brainfuck::OpCode> program;
  };

  struct Counters {
    std::size_t cell = 0;
    std::size_t program = 0;
  };

  struct Context {
    std::span<std::uint8_t> cells;
    std::span<ai::brainfuck::OpCode> program;
    Counters counters;
  };

  Agent(Callbacks&&, Memory&&, Counters counters = {.cell = 0, .program = 0});

  [[nodiscard]] inline Context context() noexcept {
    const ai::brainfuck::Context vm_context = this->vm.context();
    return {
      .cells = {this->memory.cells.data(), this->memory.cells.size()},
      .program = {this->memory.program.data(), this->memory.program.size()},
      .counters = {
        .cell = vm_context.cell_counter,
        .program = vm_context.program_counter
      }
    };
  }

  std::size_t run(std::size_t quota) noexcept;

private:
  Callbacks callbacks;
  Memory memory;
  ai::brainfuck::VM vm;
};


