#pragma once
#include <flecs.h>
#include <memory>
#include <chrono>
#include <string>

namespace core::modules {

namespace visualization {

using namespace std::chrono_literals;

struct WindowCreate {
  std::string title = "Window";
  std::string icon;
};

struct ExitOnWindowClose {};

struct Window {};

}

struct Visualization {
  explicit Visualization(flecs::world &world);
};

} // namespace core::modules
