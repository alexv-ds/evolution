#include <stdexcept>
#include <format>
#include "brainfuck.hpp"
#include "brainfuck/opcode_executors.hpp"

namespace ai::brainfuck {
  VM::VM(ai::brainfuck::Context context) : context_(context) {
    if (context.program_counter >= context.program.size()) {
      throw std::runtime_error(
        std::format(
          "context.program_counter ({}) >= context.program.size ({})",
          context.program_counter, context.program.size()
        )
      );
    }

    if (context.cell_counter >= context.cells.size()) {
      throw std::runtime_error(
        std::format(
          "context.cell_counter ({}) >= context.cells.size ({})",
          context.cell_counter, context.cells.size()
        )
      );
    }
  }

  inline static void fix_counters(Context& context) {
    if (context.program_counter >= context.program.size()) {
      context.program_counter = 0;
    }

    if (context.cell_counter >= context.cells.size()) {
      context.cell_counter = 0;
    }
  }

  SuspendReason VM::run(std::size_t quota) noexcept {
    while (quota > 0) {
      --quota;

      switch (this->context_.program[this->context_.program_counter]) {
        case OpCode::NEXT_CELL: {
          executors::cell_next(this->context_);
          break;
        }
        case OpCode::PREV_CELL: {
          executors::cell_prev(this->context_);
          break;
        }
        case OpCode::INCREMENT: {
          executors::cell_increment(this->context_);
          break;
        }
        case OpCode::DECREMENT: {
          executors::cell_decrement(this->context_);
          break;
        }
        case OpCode::PUT: {
          const std::size_t cell_index = executors::put(this->context_);
          fix_counters(this->context_);
          return {
            .quota = quota,
            .action = PutAction{
              .cell = &this->context_.cells[cell_index]
            }
          };
        }
        case OpCode::READ: {
          const std::size_t cell_index = executors::read(this->context_);
          fix_counters(this->context_);
          return {
            .quota = quota,
            .action = ReadAction{
              .cell = &this->context_.cells[cell_index]
            }
          };
        }
        case OpCode::OPEN_BRACKET: {
          executors::bracket_open(this->context_);
          break;
        }
        case OpCode::CLOSE_BRACKET: {
          executors::bracket_close(this->context_);
          break;
        }
        default: {
          ++this->context_.program_counter;
          break;
        }
      }

      fix_counters(this->context_);
    }

    return {
      .quota = quota,
      .action = std::monostate{}
    };
  }


} // namespace ai::brainfuck





