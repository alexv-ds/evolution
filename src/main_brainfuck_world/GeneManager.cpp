// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <bit>
#include "GeneManager.hpp"


GeneManager::Genes GeneManager::create(GeneManager::NewGenerationSettings settings) {
  Genes genes = {
    .cells = settings.cells_size,
    .program = decltype(genes.program)(settings.program_size, {}),
  };

  for (auto& opcode: genes.program) {
    opcode = this->generate_opcode();
  }

  return genes;
}

void GeneManager::mutate(GeneManager::Genes& genes) {
  std::uniform_int_distribution<std::size_t> mutation_point(0, genes.program.size()-1);
  for (std::size_t i = 0; i < 5; ++i) {
    const std::size_t write_index = mutation_point(this->random_generator);
    genes.program.at(write_index) = this->generate_opcode();
  }
}

GeneManager::GeneManager() :
  random_generator([]() {
    std::random_device rd;
    return rd();
  }()) {
  this->dist_full_or_real_opcode = decltype(this->dist_full_or_real_opcode)(0, 100);
  this->dist_full_random_opcode = decltype(this->dist_full_random_opcode)(0, 255);
  this->dist_real_opcode = decltype(this->dist_real_opcode)(0, this->real_opcodes.size());
}

ai::brainfuck::OpCode GeneManager::generate_opcode() {
  ai::brainfuck::OpCode opcode;

  if (this->dist_full_or_real_opcode(this->random_generator) < 30) {
    opcode = this->real_opcodes[this->dist_real_opcode(this->random_generator)];
  } else {
    opcode = std::bit_cast<decltype(opcode)>(this->dist_full_random_opcode(this->random_generator));
  }

  return opcode;
}
