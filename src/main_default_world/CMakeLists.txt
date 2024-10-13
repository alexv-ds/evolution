add_executable(evolution
  main.cpp
  init_world.cpp
  $<$<BOOL:${WIN32}>:icon.rc>
)
target_compile_options(evolution PRIVATE ${EVO_DEFAULT_TARGET_FLAGS})

target_link_libraries(evolution PRIVATE evolution::core)

add_custom_command(TARGET evolution POST_BUILD
  COMMAND cmake -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/icon512.png" "$<TARGET_FILE_DIR:evolution>/icon.png"
)
