add_library(evolution-ai
  brainfuck/opcode_executors.hpp
  brainfuck/types.hpp
  brainfuck.hpp
  brainfuck.cpp
)
add_library(evolution::ai ALIAS evolution-ai)

target_include_directories(evolution-ai PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")

target_compile_options(evolution-ai PRIVATE ${EVO_DEFAULT_TARGET_FLAGS})

target_link_libraries(evolution-ai PUBLIC Boost::core)
