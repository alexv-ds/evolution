
add_executable(evolution-brainfuck-world
  main.cpp
  Agent.cpp
  Agent.hpp
  GeneManager.cpp
  GeneManager.hpp
  ITester.hpp
  testers/HelloWorld.cpp
  testers/HelloWorld.hpp
)
target_compile_options(evolution-brainfuck-world PRIVATE ${EVO_DEFAULT_TARGET_FLAGS})
target_link_libraries(evolution-brainfuck-world PRIVATE
  evolution::core
  evolution::ai
  Boost::core
  fpimpl::fpimpl
)
