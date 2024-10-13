#pragma once

namespace core::helpers {

void fix_win_console();
void init_spdlog();
void redirect_flecs_logs_to_spdlog();

}
