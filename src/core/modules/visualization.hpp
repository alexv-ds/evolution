#pragma once
#include <flecs.h>
#include <memory>
#include <chrono>

namespace core::modules {

namespace visualization {

using namespace std::chrono_literals;

struct WindowCreate {
  std::string title = "Window";
};

struct ExitOnWindowClose {};

struct Window {};

}

struct Visualization {
  explicit Visualization(flecs::world &world);
};

} // namespace core::modules
