#pragma once

#include <vector>
#include <random>
#include <ai/brainfuck.hpp>

class GeneManager {
public:
  struct Genes {
    std::size_t cells = 0;
    std::vector<ai::brainfuck::OpCode> program;
  };

  struct NewGenerationSettings {
    std::size_t cells_size = 0;
    std::size_t program_size = 0;
  };

  struct MutateSettings {
  };

  GeneManager();

  Genes create(NewGenerationSettings settings);

  template<std::output_iterator<Genes> OutputIt>
  void create(OutputIt out, std::size_t n, NewGenerationSettings settings);

  void mutate(Genes& genes);

  template<std::forward_iterator It>
  requires std::is_same_v<typename It::value_type, Genes>
  void mutate(const It begin, const It end) {
    for (std::forward_iterator auto it = begin; it != end; ++it) {
      this->mutate(*it);
    }
  }

  ai::brainfuck::OpCode generate_opcode();


private:
  std::mt19937 random_generator;

  std::uniform_int_distribution<int> dist_full_or_real_opcode;
  std::uniform_int_distribution<std::uint8_t> dist_full_random_opcode;
  std::uniform_int_distribution<std::size_t> dist_real_opcode;
  std::array<ai::brainfuck::OpCode, 8> real_opcodes = {
    ai::brainfuck::OpCode::NEXT_CELL,
    ai::brainfuck::OpCode::PREV_CELL,
    ai::brainfuck::OpCode::INCREMENT,
    ai::brainfuck::OpCode::DECREMENT,
    ai::brainfuck::OpCode::PUT,
    ai::brainfuck::OpCode::READ,
    ai::brainfuck::OpCode::OPEN_BRACKET,
    ai::brainfuck::OpCode::CLOSE_BRACKET
  };
};

//////////////
template<std::output_iterator<GeneManager::Genes> OutputIt>
void GeneManager::create(OutputIt out, const std::size_t n, const NewGenerationSettings settings) {
  for (std::size_t i = 0; i < n; ++i) {
    *out++ = std::move(this->create(settings));
  }
}
