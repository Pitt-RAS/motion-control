include(../../../CompilerFlags.cmake)

include_directories(include)

add_library(sysfs_gpio src/gpio.cpp)

add_executable(sysfs_gpio_export tools/export.cpp)
add_executable(sysfs_gpio_unexport tools/unexport.cpp)

find_library(PTHREAD pthread)

target_link_libraries(sysfs_gpio_export sysfs_gpio ${PTHREAD})
target_link_libraries(sysfs_gpio_unexport sysfs_gpio ${PTHREAD})
