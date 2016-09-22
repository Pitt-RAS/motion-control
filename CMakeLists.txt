cmake_minimum_required(VERSION 3.0)
project(motion-control)
message("Starting build on ${CMAKE_SYSTEM_NAME}")

include_directories(include)

set(SOURCE_FILES src/dummy.cpp)
set(CMAKE_CXX_FLAGS -std=c++11)

add_library(motion_control ${SOURCE_FILES})


if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  message("Building Linux sysfs gpio driver")
  add_subdirectory(src/modules/sysfs_gpio)
endif()
