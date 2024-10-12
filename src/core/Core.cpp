//
// Created by alexv on 12.10.24.
//

#include "Core.hpp"

namespace core {

Core::Core() : world_(std::make_shared<flecs::world>()) {}

std::shared_ptr<Core> Core::create() {
  struct make_shared_enabler : Core {};
  std::shared_ptr<Core> core = std::make_shared<make_shared_enabler>();
  core->initialize();
  return core;
}

void Core::initialize() {
  world_->component<core_ptr>("::core::core_ptr");
  world_->set<core_ptr>(std::move(this->weak_from_this()));
}

void Core::run() {
  if (this->is_running) {
    throw std::logic_error("Core::run: core already running");
  }
  this->is_running = true;
  world_->app()
      .target_fps(60)
      .enable_rest()
      .enable_stats()
      .threads(static_cast<std::int32_t>(std::thread::hardware_concurrency()))
      .run();
  this->is_running = false;
}



} // namespace core
