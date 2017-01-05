include(../CompilerFlags.cmake)

cmake_minimum_required(VERSION 3.0)
project(motion_control_test)

include_directories(include)

add_executable(motion_control_test
  main.cpp
  test_time.cpp
  test_trapezoidal_motion.cpp
  test_instance_list.cpp
  test_runner.cpp
  test_math.cpp
  test_system.cpp
)

target_link_libraries(motion_control_test motion_control)
