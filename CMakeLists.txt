cmake_minimum_required(VERSION 3.0)
project(motion-control)


include(CompilerFlags.cmake)


# Main Library
include_directories(include)
add_library(motion_control src/dummy.cpp src/platforms/${CMAKE_SYSTEM_NAME}/time.cpp src/time.cpp src/trapezoidal_motion_profile.cpp src/runner.cpp src/runnable.cpp)


# Modules
message("System is ${CMAKE_SYSTEM_NAME}")

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  message("Sysfs GPIO module enabled")
  add_subdirectory(src/modules/sysfs_gpio)
else()
  message("Sysfs GPIO module disabled")
endif()


if (${BUILD_TEST})
    add_subdirectory(test)
endif()
