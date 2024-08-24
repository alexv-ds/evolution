add_executable(tests-ai-brainfuck
  opcode_executors.cpp
  vm.cpp
)
target_link_libraries(tests-ai-brainfuck PRIVATE Catch2::Catch2WithMain evolution::ai)
target_compile_options(tests-ai-brainfuck PRIVATE ${EVO_DEFAULT_TARGET_FLAGS})
catch_discover_tests(tests-ai-brainfuck)

