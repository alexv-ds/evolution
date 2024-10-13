#include <flecs.h>
#include <spdlog/cfg/env.h>
#include <spdlog/spdlog.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "init.hpp"

namespace core::helpers {

void fix_win_console() {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
#endif
}

void init_spdlog() {
#ifdef SPDLOG_ACTIVE_LEVEL
  spdlog::set_level(
      static_cast<spdlog::level::level_enum>(SPDLOG_ACTIVE_LEVEL));
#endif
  spdlog::cfg::load_env_levels();
}

void redirect_flecs_logs_to_spdlog() {
  // ecs_os_api_log_t
  // ecs_os_set_api
  ecs_os_set_api_defaults();
  ecs_log_enable_colors(false);

  ecs_os_api_t os_api = ecs_os_get_api();

  os_api.log_ = [](int32_t flecs_level, const char *file, int32_t line,
                   const char *msg) {
    // SPDLOG_INFO();
    const spdlog::level::level_enum spdlog_level = [flecs_level]() {
      if (flecs_level > 0) {
        return spdlog::level::trace;
      }
      if (flecs_level == 0) {
        return spdlog::level::debug;
      }
      if (flecs_level == -2) {
        return spdlog::level::warn;
      }
      if (flecs_level == -3) {
        return spdlog::level::err;
      }
      return spdlog::level::critical;
    }();

    spdlog::default_logger_raw()->log({file, line, nullptr}, spdlog_level, msg);
  };

  ecs_os_set_api(&os_api);
}

} // namespace core::helpers
