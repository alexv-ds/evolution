#include <string>
#include <vector>
#include <catch2/catch_test_macros.hpp>
#include <ai/brainfuck/opcode_executors.hpp>

using namespace ai::brainfuck;

SCENARIO("Brainfuck executor - cell_next moves cell counter") {
  GIVEN(R"(Context: cells - "111", program ">>>" , program counter - 0, cell counter - 0)") {

    std::vector<std::uint8_t> cells = {'1', '1', '1'};
    std::vector<OpCode> program = {
      OpCode::NEXT_CELL,
      OpCode::NEXT_CELL,
      OpCode::NEXT_CELL,
    };
    Context context = {
      .cells = {cells.data(), cells.size()},
      .program = {program.data(), program.size()},
      .program_counter = 0,
      .cell_counter = 0
    };

    WHEN("execute cell_next once") {
      executors::cell_next(context);
      THEN("cells - '111'") {
        REQUIRE(cells.size() == 3);
        REQUIRE(cells.at(0) == '1');
        REQUIRE(cells.at(1) == '1');
        REQUIRE(cells.at(2) == '1');
      }

      THEN("program - '>>>'") {
        REQUIRE(program.size() == 3);
        REQUIRE(program.at(0) == OpCode::NEXT_CELL);
        REQUIRE(program.at(1) == OpCode::NEXT_CELL);
        REQUIRE(program.at(2) == OpCode::NEXT_CELL);
      }

      THEN("program counter - 1") {
        REQUIRE(context.program_counter == 1);
      }

      THEN("cells counter - 1") {
        REQUIRE(context.cell_counter == 1);
      }
    }

    WHEN("execute cell_next 3 times") {
      executors::cell_next(context);
      executors::cell_next(context);
      executors::cell_next(context);

      THEN("cells - '111'") {
        REQUIRE(cells.size() == 3);
        REQUIRE(cells.at(0) == '1');
        REQUIRE(cells.at(1) == '1');
        REQUIRE(cells.at(2) == '1');
      }

      THEN("program - '>>>'") {
        REQUIRE(program.size() == 3);
        REQUIRE(program.at(0) == OpCode::NEXT_CELL);
        REQUIRE(program.at(1) == OpCode::NEXT_CELL);
        REQUIRE(program.at(2) == OpCode::NEXT_CELL);
      }

      THEN("program counter - 3") {
        REQUIRE(context.program_counter == 3);
      }

      THEN("cells counter - 3") {
        REQUIRE(context.cell_counter == 3);
      }
    }
  }
}

SCENARIO("Brainfuck executor - cell_prev moves cell counter") {
  GIVEN(R"(Context: cells - "111", program "<<<" , program counter - 0, cell counter - 1)") {
    std::vector<std::uint8_t> cells = {'1', '1', '1'};
    std::vector<OpCode> program = {
      OpCode::PREV_CELL,
      OpCode::PREV_CELL,
      OpCode::PREV_CELL,
    };
    Context context = {
      .cells = {cells.data(), cells.size()},
      .program = {program.data(), program.size()},
      .program_counter = 0,
      .cell_counter = 2
    };

    WHEN("execute cell_prev once") {
      executors::cell_prev(context);
      THEN("cells - '111'") {
        REQUIRE(cells.size() == 3);
        REQUIRE(cells.at(0) == '1');
        REQUIRE(cells.at(1) == '1');
        REQUIRE(cells.at(2) == '1');
      }

      THEN("program - '<<<'") {
        REQUIRE(program.size() == 3);
        REQUIRE(program.at(0) == OpCode::PREV_CELL);
        REQUIRE(program.at(1) == OpCode::PREV_CELL);
        REQUIRE(program.at(2) == OpCode::PREV_CELL);
      }

      THEN("program counter - 1") {
        REQUIRE(context.program_counter == 1);
      }

      THEN("cells counter - 1") {
        REQUIRE(context.cell_counter == 1);
      }
    }

    WHEN("execute cell_prev 2 times") {
      executors::cell_prev(context);
      executors::cell_prev(context);

      THEN("cells - '111'") {
        REQUIRE(cells.size() == 3);
        REQUIRE(cells.at(0) == '1');
        REQUIRE(cells.at(1) == '1');
        REQUIRE(cells.at(2) == '1');
      }

      THEN("program - '<<<'") {
        REQUIRE(program.size() == 3);
        REQUIRE(program.at(0) == OpCode::PREV_CELL);
        REQUIRE(program.at(1) == OpCode::PREV_CELL);
        REQUIRE(program.at(2) == OpCode::PREV_CELL);
      }

      THEN("program counter - 2") {
        REQUIRE(context.program_counter == 2);
      }

      THEN("cells counter - 0") {
        REQUIRE(context.cell_counter == 0);
      }
    }
  }
}

SCENARIO("Brainfuck executor - cell_increment increments cell") {
  GIVEN("Context: cells - {0}, program '+++' , program counter - 0, cell counter - 0") {
    std::vector<std::uint8_t> cells = {0};
    const std::vector<OpCode> program = {
      OpCode::INCREMENT,
      OpCode::INCREMENT,
      OpCode::INCREMENT,
    };
    Context context = {
      .cells = {cells.data(), cells.size()},
      .program = {program.data(), program.size()},
      .program_counter = 0,
      .cell_counter = 0
    };

    WHEN("execute cell_increment once") {
      executors::cell_increment(context);

      THEN("program counter == 1") {
        REQUIRE(context.program_counter == 1);
      }

      THEN("cells counter == 0") {
        REQUIRE(context.cell_counter == 0);
      }

      THEN("cells == {1}") {
        REQUIRE(cells.size() == 1);
        REQUIRE(cells.at(0) == 1);
      }
    }

    WHEN("execute cell_increment 3 times") {
      executors::cell_increment(context);
      executors::cell_increment(context);
      executors::cell_increment(context);

      THEN("program counter == 3") {
        REQUIRE(context.program_counter == 3);
      }

      THEN("cells counter == 0") {
        REQUIRE(context.cell_counter == 0);
      }

      THEN("cells == {3}") {
        REQUIRE(cells.size() == 1);
        REQUIRE(cells.at(0) == 3);
      }
    }

  }
}

SCENARIO("Brainfuck executor - cell_decrement decrements cell") {
  GIVEN("Context: cells - {100}, program '---' , program counter - 0, cell counter - 0") {
    std::vector<std::uint8_t> cells = {100};
    const std::vector<OpCode> program = {
      OpCode::DECREMENT,
      OpCode::DECREMENT,
      OpCode::DECREMENT,
    };
    Context context = {
      .cells = {cells.data(), cells.size()},
      .program = {program.data(), program.size()},
      .program_counter = 0,
      .cell_counter = 0
    };

    WHEN("execute cell_decrement once") {
      executors::cell_decrement(context);

      THEN("program counter == 1") {
        REQUIRE(context.program_counter == 1);
      }

      THEN("cells counter == 0") {
        REQUIRE(context.cell_counter == 0);
      }

      THEN("cells == {99}") {
        REQUIRE(cells.size() == 1);
        REQUIRE(cells.at(0) == 99);
      }
    }

    WHEN("execute cell_decrement 3 times") {
      executors::cell_decrement(context);
      executors::cell_decrement(context);
      executors::cell_decrement(context);

      THEN("program counter == 3") {
        REQUIRE(context.program_counter == 3);
      }

      THEN("cells counter == 0") {
        REQUIRE(context.cell_counter == 0);
      }

      THEN("cells == {97}") {
        REQUIRE(cells.size() == 1);
        REQUIRE(cells.at(0) == 97);
      }
    }
  }
}

SCENARIO("Brainfuck executor - put returns current cell index") {
  GIVEN("Context: cells - {1,2,3,4}, program '.' , program counter - 0, cells counter - 2") {
    std::vector<std::uint8_t> cells = {1, 2, 3, 4};
    const std::vector<OpCode> program = {OpCode::PUT};
    Context context = {
      .cells = {cells.data(), cells.size()},
      .program = {program.data(), program.size()},
      .program_counter = 0,
      .cell_counter = 2
    };

    WHEN("execute put once") {
      const std::size_t index = executors::put(context);

      THEN("cells == {1,2,3,4}") {
        REQUIRE(context.cells.size() == 4);
        REQUIRE(context.cells[0] == 1);
        REQUIRE(context.cells[1] == 2);
        REQUIRE(context.cells[2] == 3);
        REQUIRE(context.cells[3] == 4);
      }

      THEN("program == '.'") {
        REQUIRE(context.program.size() == 1);
        REQUIRE(context.program[0] == OpCode::PUT);
      }

      THEN("program counter == 1") {
        REQUIRE(context.program_counter == 1);
      }

      THEN("cell counter == 2") {
        REQUIRE(context.cell_counter == 2);
      }

      THEN("returned index == 2") {
        REQUIRE(index == 2);
      }
    }
  }
}

SCENARIO("Brainfuck executor - read returns current cell index") {
  GIVEN("Context: cells - {1,2,3,4}, program ',' , program counter - 0, cells counter - 2") {
    std::vector<std::uint8_t> cells = {1, 2, 3, 4};
    const std::vector<OpCode> program = {OpCode::READ};
    Context context = {
      .cells = {cells.data(), cells.size()},
      .program = {program.data(), program.size()},
      .program_counter = 0,
      .cell_counter = 2
    };

    WHEN("execute put once") {
      const std::size_t index = executors::read(context);

      THEN("cells == {1,2,3,4}") {
        REQUIRE(context.cells.size() == 4);
        REQUIRE(context.cells[0] == 1);
        REQUIRE(context.cells[1] == 2);
        REQUIRE(context.cells[2] == 3);
        REQUIRE(context.cells[3] == 4);
      }

      THEN("program == ','") {
        REQUIRE(context.program.size() == 1);
        REQUIRE(context.program[0] == OpCode::READ);
      }

      THEN("program counter == 1") {
        REQUIRE(context.program_counter == 1);
      }

      THEN("cell counter == 2") {
        REQUIRE(context.cell_counter == 2);
      }

      THEN("returned index == 2") {
        REQUIRE(index == 2);
      }
    }
  }
}

SCENARIO("Brainfuck executor - bracket_open correctly moves program counter") {

  GIVEN("Context: cells - {1}, program '[...]...' , program counter - 0, cells counter - 0") {
    std::vector<std::uint8_t> cells = {1};
    const std::string program = "[...]...";
    Context context{
      .cells = {cells.data(), cells.size()},
      .program = {reinterpret_cast<const OpCode*>(program.data()), program.size()},
      .program_counter = 0,
      .cell_counter = 0
    };

    WHEN("execute bracket_open") {
      executors::bracket_open(context);

      THEN("cells == {1}") {
        REQUIRE(context.cells[0] == 1);
      }

      THEN("cell counter == 0") {
        REQUIRE(context.cell_counter == 0);
      }

      THEN("program counter == 1") {
        REQUIRE(context.program_counter == 1);
      }
    }
  }

  GIVEN("Context: cells - {0}, program '[...]...' , program counter - 0, cells counter - 0") {
    std::vector<std::uint8_t> cells = {0};
    const std::string program = "[...]...";
    Context context{
      .cells = {cells.data(), cells.size()},
      .program = {reinterpret_cast<const OpCode*>(program.data()), program.size()},
      .program_counter = 0,
      .cell_counter = 0
    };

    WHEN("execute bracket_open") {
      executors::bracket_open(context);

      THEN("cells == {0}") {
        REQUIRE(context.cells[0] == 0);
      }

      THEN("cell counter == 0") {
        REQUIRE(context.cell_counter == 0);
      }

      THEN("program counter == 5") {
        REQUIRE(context.program_counter == 5);
      }
    }
  }

  GIVEN("Context: cells - {0}, program '[...]' , program counter - 0, cells counter - 0") {
    std::vector<std::uint8_t> cells = {0};
    const std::string program = "[...]";
    Context context{
      .cells = {cells.data(), cells.size()},
      .program = {reinterpret_cast<const OpCode*>(program.data()), program.size()},
      .program_counter = 0,
      .cell_counter = 0
    };

    WHEN("execute bracket_open") {
      executors::bracket_open(context);

      THEN("cells == {0}") {
        REQUIRE(context.cells[0] == 0);
      }

      THEN("cell counter == 0") {
        REQUIRE(context.cell_counter == 0);
      }

      THEN("program counter == 5") {
        REQUIRE(context.program_counter == 5);
      }
    }
  }

  GIVEN("Context: cells - {0}, program '[...' , program counter - 0, cells counter - 0") {
    std::vector<std::uint8_t> cells = {0};
    const std::string program = "[...";
    Context context{
      .cells = {cells.data(), cells.size()},
      .program = {reinterpret_cast<const OpCode*>(program.data()), program.size()},
      .program_counter = 0,
      .cell_counter = 0
    };

    WHEN("execute bracket_open") {
      executors::bracket_open(context);

      THEN("cells == {0}") {
        REQUIRE(context.cells[0] == 0);
      }

      THEN("cell counter == 0") {
        REQUIRE(context.cell_counter == 0);
      }

      THEN("program counter == 4") {
        REQUIRE(context.program_counter == 4);
      }
    }
  }

  GIVEN("Context: cells - {0}, program '...' , program counter - 0, cells counter - 0") {
    std::vector<std::uint8_t> cells = {0};
    const std::string program = "...";
    Context context{
      .cells = {cells.data(), cells.size()},
      .program = {reinterpret_cast<const OpCode*>(program.data()), program.size()},
      .program_counter = 0,
      .cell_counter = 0
    };

    WHEN("execute bracket_open") {
      executors::bracket_open(context);

      THEN("cells == {0}") {
        REQUIRE(context.cells[0] == 0);
      }

      THEN("cell counter == 0") {
        REQUIRE(context.cell_counter == 0);
      }

      THEN("program counter == 3") {
        REQUIRE(context.program_counter == 3);
      }
    }
  }

  GIVEN("Context: cells - {0}, program '[.[..].]' , program counter - 0, cells counter - 0") {
    std::vector<std::uint8_t> cells = {0};
    const std::string program = "[.[..].]";
    Context context{
      .cells = {cells.data(), cells.size()},
      .program = {reinterpret_cast<const OpCode*>(program.data()), program.size()},
      .program_counter = 0,
      .cell_counter = 0
    };

    WHEN("execute bracket_open") {
      executors::bracket_open(context);

      THEN("cells == {0}") {
        REQUIRE(context.cells[0] == 0);
      }

      THEN("cell counter == 0") {
        REQUIRE(context.cell_counter == 0);
      }

      THEN("program counter == 8") {
        REQUIRE(context.program_counter == 8);
      }
    }
  }

  GIVEN("Context: cells - {0}, program '[.[..].]' , program counter - 2, cells counter - 0") {
    std::vector<std::uint8_t> cells = {0};
    const std::string program = "[.[..].]";
    Context context{
      .cells = {cells.data(), cells.size()},
      .program = {reinterpret_cast<const OpCode*>(program.data()), program.size()},
      .program_counter = 2,
      .cell_counter = 0
    };

    WHEN("execute bracket_open") {
      executors::bracket_open(context);

      THEN("cells == {0}") {
        REQUIRE(context.cells[0] == 0);
      }

      THEN("cell counter == 0") {
        REQUIRE(context.cell_counter == 0);
      }

      THEN("program counter == 6") {
        REQUIRE(context.program_counter == 6);
      }
    }
  }
}

SCENARIO("Brainfuck executor - bracket_clone correctly moves program counter") {
  GIVEN("Context: cells - {0}, program '[...]...' , program counter - 4, cells counter - 0") {
    std::vector<std::uint8_t> cells = {0};
    const std::string program = "[...]...";
    Context context{
      .cells = {cells.data(), cells.size()},
      .program = {reinterpret_cast<const OpCode*>(program.data()), program.size()},
      .program_counter = 4,
      .cell_counter = 0
    };

    WHEN("execute bracket_close") {
      executors::bracket_close(context);

      THEN("cells == {0}") {
        REQUIRE(context.cells.size() == 1);
        REQUIRE(context.cells[0] == 0);
      }

      THEN("cell counter == 0") {
        REQUIRE(context.cell_counter == 0);
      }

      THEN("program counter == 5") {
        REQUIRE(context.program_counter == 5);
      }
    }
  }

  GIVEN("Context: cells - {0}, program '[...]' , program counter - 4, cells counter - 0") {
    std::vector<std::uint8_t> cells = {0};
    const std::string program = "[...]";
    Context context{
      .cells = {cells.data(), cells.size()},
      .program = {reinterpret_cast<const OpCode*>(program.data()), program.size()},
      .program_counter = 4,
      .cell_counter = 0
    };

    WHEN("execute bracket_close") {
      executors::bracket_close(context);

      THEN("cells == {0}") {
        REQUIRE(context.cells.size() == 1);
        REQUIRE(context.cells[0] == 0);
      }

      THEN("cell counter == 0") {
        REQUIRE(context.cell_counter == 0);
      }

      THEN("program counter == 5") {
        REQUIRE(context.program_counter == 5);
      }
    }
  }

  GIVEN("Context: cells - {1}, program '[...]...' , program counter - 4, cells counter - 0") {
    std::vector<std::uint8_t> cells = {1};
    const std::string program = "[...]...";
    Context context{
      .cells = {cells.data(), cells.size()},
      .program = {reinterpret_cast<const OpCode*>(program.data()), program.size()},
      .program_counter = 4,
      .cell_counter = 0
    };

    WHEN("execute bracket_close") {
      executors::bracket_close(context);

      THEN("cells == {0}") {
        REQUIRE(context.cells.size() == 1);
        REQUIRE(context.cells[0] == 1);
      }

      THEN("cell counter == 0") {
        REQUIRE(context.cell_counter == 0);
      }

      THEN("program counter == 0") {
        REQUIRE(context.program_counter == 0);
      }
    }
  }

  GIVEN("Context: cells - {1}, program '[.[.].]' , program counter - 6, cells counter - 0") {
    std::vector<std::uint8_t> cells = {1};
    const std::string program = "[.[.].]";
    Context context{
      .cells = {cells.data(), cells.size()},
      .program = {reinterpret_cast<const OpCode*>(program.data()), program.size()},
      .program_counter = 6,
      .cell_counter = 0
    };

    WHEN("execute bracket_close") {
      executors::bracket_close(context);

      THEN("cells == {0}") {
        REQUIRE(context.cells.size() == 1);
        REQUIRE(context.cells[0] == 1);
      }

      THEN("cell counter == 0") {
        REQUIRE(context.cell_counter == 0);
      }

      THEN("program counter == 0") {
        REQUIRE(context.program_counter == 0);
      }
    }
  }

  GIVEN("Context: cells - {1}, program '[.[.].]' , program counter - 4, cells counter - 0") {
    std::vector<std::uint8_t> cells = {1};
    const std::string program = "[.[.].]";
    Context context{
      .cells = {cells.data(), cells.size()},
      .program = {reinterpret_cast<const OpCode*>(program.data()), program.size()},
      .program_counter = 4,
      .cell_counter = 0
    };

    WHEN("execute bracket_close") {
      executors::bracket_close(context);

      THEN("cells == {0}") {
        REQUIRE(context.cells.size() == 1);
        REQUIRE(context.cells[0] == 1);
      }

      THEN("cell counter == 0") {
        REQUIRE(context.cell_counter == 0);
      }

      THEN("program counter == 2") {
        REQUIRE(context.program_counter == 2);
      }
    }
  }

  GIVEN("Context: cells - {1}, program '..[.].]' , program counter - 4, cells counter - 0") {
    std::vector<std::uint8_t> cells = {1};
    const std::string program = "..[.].]";
    Context context{
      .cells = {cells.data(), cells.size()},
      .program = {reinterpret_cast<const OpCode*>(program.data()), program.size()},
      .program_counter = 4,
      .cell_counter = 0
    };

    WHEN("execute bracket_close") {
      executors::bracket_close(context);

      THEN("cells == {0}") {
        REQUIRE(context.cells.size() == 1);
        REQUIRE(context.cells[0] == 1);
      }

      THEN("cell counter == 0") {
        REQUIRE(context.cell_counter == 0);
      }

      THEN("program counter == 2") {
        REQUIRE(context.program_counter == 2);
      }
    }
  }

  GIVEN("Context: cells - {1}, program '..[.].]' , program counter - 6, cells counter - 0") {
    std::vector<std::uint8_t> cells = {1};
    const std::string program = "..[.].]";
    Context context{
      .cells = {cells.data(), cells.size()},
      .program = {reinterpret_cast<const OpCode*>(program.data()), program.size()},
      .program_counter = 6,
      .cell_counter = 0
    };

    WHEN("execute bracket_close") {
      executors::bracket_close(context);

      THEN("cells == {0}") {
        REQUIRE(context.cells.size() == 1);
        REQUIRE(context.cells[0] == 1);
      }

      THEN("cell counter == 0") {
        REQUIRE(context.cell_counter == 0);
      }

      THEN("program counter == 0") {
        REQUIRE(context.program_counter == 0);
      }
    }
  }

  GIVEN("Context: cells - {1}, program '......]' , program counter - 6, cells counter - 0") {
    std::vector<std::uint8_t> cells = {1};
    const std::string program = "......]";
    Context context{
      .cells = {cells.data(), cells.size()},
      .program = {reinterpret_cast<const OpCode*>(program.data()), program.size()},
      .program_counter = 6,
      .cell_counter = 0
    };

    WHEN("execute bracket_close") {
      executors::bracket_close(context);

      THEN("cells == {0}") {
        REQUIRE(context.cells.size() == 1);
        REQUIRE(context.cells[0] == 1);
      }

      THEN("cell counter == 0") {
        REQUIRE(context.cell_counter == 0);
      }

      THEN("program counter == 0") {
        REQUIRE(context.program_counter == 0);
      }
    }
  }
}
