add_subdirectory(core)

add_executable(evolution
  main.cpp
  init_world.cpp
)
target_compile_options(evolution PRIVATE ${EVO_DEFAULT_TARGET_FLAGS})

target_link_libraries(evolution PRIVATE evolution::core)
