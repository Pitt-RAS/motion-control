project(motion_control_test)
enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})



add_executable(motion_control_test test_time.cpp test_fixedsizestack.cpp test_trapezoidal_motion.cpp)
target_link_libraries(motion_control_test motion_control gtest gtest_main)