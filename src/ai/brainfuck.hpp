#pragma once

#include <variant>
#include <boost/noncopyable.hpp>
#include "brainfuck/types.hpp"

namespace ai::brainfuck {

  struct PutAction {
    const std::uint8_t* cell = nullptr;
  };

  struct ReadAction {
    std::uint8_t* cell = nullptr;
  };

  using Action = std::variant<std::monostate, PutAction, ReadAction>;

  struct SuspendReason {
    std::size_t quota = 0;
    Action action = std::monostate{};
  };

  class VM : public boost::noncopyable {
  public:
    explicit VM(ai::brainfuck::Context context);

    SuspendReason run(std::size_t quota) noexcept;

    inline Context context() const noexcept {
      return this->context_;
    }

  private:
    Context context_;
  };


} // namespace ai::brainfuck
