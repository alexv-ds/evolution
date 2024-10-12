#include <core/helpers/time_measuring.hpp>
#include <flecs.h>
#include <spdlog/spdlog.h>

#include <core/Core.hpp>

using namespace core;

void init_world(flecs::world &);

int main() {
#ifdef SPDLOG_ACTIVE_LEVEL
  spdlog::set_level(
      static_cast<spdlog::level::level_enum>(SPDLOG_ACTIVE_LEVEL));
#endif

  std::shared_ptr core = Core::create();

  {
    const helpers::TimeMeasuring init_measure;
    init_world(*core->world());
    const auto duration = init_measure.measure<std::chrono::duration<float>>();
    SPDLOG_INFO("World initialised - {0:.2f}s", duration.count());
  }

  SPDLOG_TRACE("World run");
  core->run();
}
