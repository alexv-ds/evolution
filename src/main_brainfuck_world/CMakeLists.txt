
add_executable(evolution-brainfuck-world
  main.cpp
)
target_compile_options(evolution-brainfuck-world PRIVATE ${EVO_DEFAULT_TARGET_FLAGS})
target_link_libraries(evolution-brainfuck-world PRIVATE
  evolution::core
  evolution::ai
)
