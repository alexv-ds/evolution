// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <cmath>
#include <spdlog/spdlog.h>
#include "../Agent.hpp"
#include "HelloWorld.hpp"

namespace testers {
//  bool HelloWorld::on_put(std::uint8_t cell) {
//    SPDLOG_TRACE("PUT CALLBACK: {}", (char) cell);
//    return true;
//  }
//
//  bool HelloWorld::on_read(uint8_t&) {
//    SPDLOG_TRACE("READ CALLBACK");
//    return true;
//  }
//
//  Agent::Callbacks HelloWorld::callbacks() {
//    return {
//      .put = [shared_this = this->shared_from_this()](const std::uint8_t cell){
//        return shared_this->on_put(cell);
//      },
//      .read = [shared_this = this->shared_from_this()](std::uint8_t& cell){
//        return shared_this->on_read(std::ref(cell));
//      }
//    };
//  }
//
//  std::uint32_t HelloWorld::score(std::size_t used_quota) {
//    return 0;
//  }

  HelloWorld::HelloWorld(std::string&& expected_output) : expected_output(std::move(expected_output)) {
    if (this->expected_output.empty()) {
      throw std::logic_error("this->expected_output.empty()");
    }
  }


  HelloWorld::Result HelloWorld::test(const GeneManager::Genes& genes) const {
    std::string current_output;
    std::uint32_t max_size = 0;

    auto read_it = this->expected_output.begin();
    const auto read_it_end = this->expected_output.end();

    Agent::Callbacks callbacks {
      .put = [&current_output, &max_size, this](const std::uint8_t cell){
        const char ch = std::bit_cast<char>(cell);
        const char expected_ch = this->expected_output[current_output.size()];
        if (ch == expected_ch) {
          current_output.push_back(ch);
          max_size = std::max(max_size, static_cast<std::uint32_t>(current_output.size()));
        } else {
          current_output.clear();
        }
        return current_output != this->expected_output;
      },

      .read = [&](std::uint8_t& cell){
        if (read_it == read_it_end) {
          cell = 0;
        } else {
          cell = *read_it;
          ++read_it;
        }
        return true;
      }
    };

    Agent::Memory memory = {
      .cells = decltype(memory.cells)(genes.cells, 0),
      .program = genes.program
    };

    Agent agent(std::move(callbacks), std::move(memory));

    const std::size_t quota = 100000;
    const std::size_t remainig_quota = agent.run(quota);

    float megascore = (float)max_size * (float)quota / std::max(1.0f, (float)(quota - remainig_quota));

    return {
      //.score = (std::uint32_t )((float)max_size * (float) quota / (float)(quota - remainig_quota)),
      //.score = max_size,
      .score = (std::uint32_t)megascore,
      .used_quota = quota - remainig_quota
    };
  }


} // testers
