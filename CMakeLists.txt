cmake_minimum_required(VERSION 3.0)
project(motion-control)


# Main Library

include_directories(include)
add_library(motion_control src/dummy.cpp)


# Modules

message("System is ${CMAKE_SYSTEM_NAME}")

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  message("Sysfs GPIO module enabled")
  add_subdirectory(src/modules/sysfs_gpio)
else()
  message("Sysfs GPIO module disabled")
endif()


# Compiler Flags

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  set(STANDARD_FLAG -std=c++11)
  set(WARNING_FLAGS "-Wall -Wextra -Wpedantic -Werror")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  set(STANDARD_FLAG -std=c++11)
  set(WARNING_FLAGS "-Wall -Wextra -Wpedantic -Werror")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
  set(STANDARD_FLAG "")
  set(WARNING_FLAGS "/W4 /WX")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${STANDARD_FLAG} ${WARNING_FLAGS}")
