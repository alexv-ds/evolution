#pragma once

#include "types.hpp"

namespace ai::brainfuck::executors {

  /**
   * @note вызывающая функция отвечает за то, что
   *  program_counter в диапазоне [0,program.size()-1],
   *  cell_counter в диапазоне [0,cells.size()-1].
   *  После выполнения program_counter и cell_counter
   *  могут находиться за правой границей.
   * @param context
   */
  inline void cell_next(Context& context) noexcept {
    ++context.cell_counter;
    ++context.program_counter;
  }

  /**
   * @note вызывающая функция отвечает за то, что
   *  program_counter в диапазоне [0,program.size()-1],
   *  cell_counter в диапазоне [0,cells.size()-1].
   *  После выполнения program_counter может находиться за правой границей.
   *  А cell_counter может быть за левой границей.
   *
   * @param context
   */
  inline void cell_prev(Context& context) noexcept {
    --context.cell_counter;
    ++context.program_counter;
  }

  /**
   * @note вызывающая функция отвечает за то, что
   *  program_counter в диапазоне [0,program.size()-1],
   *  cell_counter в диапазоне [0,cells.size()-1].
   *  А после выполнения program_counter может находиться за правой границей.
   *
   * @param context
   */
  inline void cell_increment(Context& context) noexcept {
    ++context.cells[context.cell_counter];
    ++context.program_counter;
  }

  /**
   * @note вызывающая функция отвечает за то, что
   *  program_counter в диапазоне [0,program.size()-1],
   *  cell_counter в диапазоне [0,cells.size()-1].
   *  А после выполнения program_counter может находиться за правой границей.
   *
   * @param context
   */
  inline void cell_decrement(Context& context) noexcept {
    --context.cells[context.cell_counter];
    ++context.program_counter;
  }

  /**
   * @note вызывающая функция отвечает за то, что
   *  program_counter в диапазоне [0,program.size()-1],
   *  cell_counter в диапазоне [0,cells.size()-1].
   *  А после выполнения program_counter может находиться за правой границей.
   *
   * @param context
   * @return индекс ячейки для чтения
   */
  [[nodiscard]] inline std::size_t put(Context& context) noexcept {
    ++context.program_counter;
    return context.cell_counter;
  }

  /**
   * @note вызывающая функция отвечает за то, что
   *  program_counter в диапазоне [0,program.size()-1],
   *  cell_counter в диапазоне [0,cells.size()-1].
   *  А после выполнения program_counter может находиться за правой границей.
   *
   * @param context
   * @return индекс ячейки для записи
   */
  [[nodiscard]] inline std::size_t read(Context& context) noexcept {
    ++context.program_counter;
    return context.cell_counter;
  }

  /**
   * Eсли значение текущей ячейки ноль, перейти вперёд по тексту программы на символ,
   * следующий за соответствующей ] (с учётом вложенности).
   *
   * Если открывающие и закрывающие скобки несбалансированны, то программа останавливается за
   * последней ячейкой программы (индекс == program.size())
   *
   * @note вызывающая функция отвечает за то, что
   *  program_counter в диапазоне [0,program.size()-1],
   *  cell_counter в диапазоне [0,cells.size()-1].
   *  А после выполнения program_counter может находиться за правой границей.
   *
   * @param context
   */
  inline void bracket_open(Context& context) noexcept {
    if (context.cells[context.cell_counter] != 0) {
      ++context.program_counter;
      return;
    }
    ++context.program_counter;
    int bracket_balance = 1;
    while (context.program_counter < context.program.size()) {
      const OpCode opcode = context.program[context.program_counter];
      if (opcode == OpCode::OPEN_BRACKET) {
        ++bracket_balance;
      } else if (opcode == OpCode::CLOSE_BRACKET) {
        --bracket_balance;
      }
      ++context.program_counter;
      if (bracket_balance == 0) {
        return;
      }
    }
  }

  /**
   * Eсли значение текущей ячейки не нуль, перейти назад по тексту программы
   * на символ [ (с учётом вложенности).
   *
   * Если открывающие и закрывающие скобки несбалансированны, то программа останавливается на
   * первой ячейке программы (индекс == 0)
   *
   * @note вызывающая функция отвечает за то, что
   *  program_counter в диапазоне [0,program.size()-1],
   *  cell_counter в диапазоне [0,cells.size()-1].
   *  А после выполнения program_counter может находиться за правой границей.
   *
   * @param context
   */
  inline void bracket_close(Context& context) noexcept {
    if (context.cells[context.cell_counter] == 0) {
      ++context.program_counter;
      return;
    }

    if (context.program_counter == 0) {
      ++context.program_counter;
      return;
    }

    --context.program_counter;
    int bracket_balance = -1;
    while (context.program_counter > 0) {
      const OpCode opcode = context.program[context.program_counter];
      if (opcode == OpCode::OPEN_BRACKET) {
        ++bracket_balance;
      } else if (opcode == OpCode::CLOSE_BRACKET) {
        --bracket_balance;
      }
      if (bracket_balance == 0) {
        return;
      }
      --context.program_counter;
    }
  }

} // namespace ai::brainfuck::executors
