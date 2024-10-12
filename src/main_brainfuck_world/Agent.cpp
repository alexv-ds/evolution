// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <stdexcept>
#include "Agent.hpp"

Agent::Agent(Agent::Callbacks&& callbacks,
             Agent::Memory&& memory,
             Agent::Counters counters)
  : callbacks(std::move(callbacks)),
    memory(std::move(memory)),
    vm({
         .cells = {this->memory.cells.data(), this->memory.cells.size()},
         .program = {this->memory.program.data(), this->memory.program.size()},
         .program_counter = counters.program,
         .cell_counter = counters.cell
       }) {
  // ///////////////////////////////////
  if (this->callbacks.put == nullptr) {
    throw std::logic_error("callbacks.put == nullptr");
  }

  if (this->callbacks.read == nullptr) {
    throw std::logic_error("callbacks.read == nullptr");
  }
}

std::size_t Agent::run(const std::size_t quota) noexcept {
  ai::brainfuck::SuspendReason suspend_reason = {
    .quota = quota
  };

  do {
    suspend_reason = this->vm.run(suspend_reason.quota);

    if (auto* put = std::get_if<ai::brainfuck::PutAction>(&suspend_reason.action)) {
      if (!this->callbacks.put(*put->cell)) {
        break;
      }
    } else if (auto* read = std::get_if<ai::brainfuck::ReadAction>(&suspend_reason.action)) {
      if (!this->callbacks.read(std::ref(*read->cell))) {
        break;
      }
    }

  } while (suspend_reason.quota != 0);

  return suspend_reason.quota;
}
