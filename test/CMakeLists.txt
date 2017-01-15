include(../CompilerFlags.cmake)

include_directories(include)

add_executable(test_motion_control
  main.cpp
  test_time.cpp
  test_trapezoidal_motion.cpp
  test_instance_list.cpp
  test_runner.cpp
  test_math.cpp
  test_system.cpp
)

target_link_libraries(test_motion_control motion_control)
