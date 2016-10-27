cmake_minimum_required(VERSION 3.0)
project(motion-control)

# Set the target name to the system we are building on
# Need to look into how this behavies when crosscompiling
set(TARGET_BUILD_PLATFORM ${CMAKE_SYSTEM_NAME})


# Main Library
include_directories(include)
add_library(motion_control src/dummy.cpp src/platforms/${TARGET_BUILD_PLATFORM}/Time.cpp src/Time.cpp src/FixedSizeStack.cpp src/TrapezoidalMotionProfile.cpp src/MotionProfile1D.cpp)


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

if (BUILD_TEST)
  add_subdirectory(gtest)
  set(BUILD_GMOCK OFF)
  set(BUILD_GTEST ON)
  add_subdirectory(src/test)
endif()