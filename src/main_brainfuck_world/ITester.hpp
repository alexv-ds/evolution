#pragma once
#include "Agent.hpp"
#include "GeneManager.hpp"

// Интерфейс тестировщика для коммуникации с агентом и оценки его итогового счета

class ITester {
public:
  struct Result {
    std::uint32_t score;
    std::size_t used_quota;
  };

  [[nodiscard]] virtual Result test(const GeneManager::Genes&) const = 0;
  virtual ~ITester() = default;
};
