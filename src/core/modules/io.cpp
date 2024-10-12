
#include "io.hpp"
#include <spdlog/spdlog.h>

namespace core::modules::io {
static void PollContext(const IO &io) {
  const auto &context = io.context();
  context->poll();
}

} // namespace core::modules::io

core::modules::IO::IO(const flecs::world &world)
    : context_(std::move(std::make_shared<boost::asio::io_context>())) {
  using namespace io;

  world.module<IO>("::core::io");

  world.system<const IO>("systems::PollContext")
      .kind(flecs::PreFrame)
      .term_at(0)
      .singleton()
      .each(PollContext);
}
