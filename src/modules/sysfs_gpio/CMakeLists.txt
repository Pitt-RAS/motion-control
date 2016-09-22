include_directories(include)

add_library(sysfs_gpio src/gpio.cpp)

add_executable(sysfs_export tools/export.cpp)
add_executable(sysfs_unexport tools/unexport.cpp)
target_link_libraries(sysfs_export sysfs_gpio pthread)
target_link_libraries(sysfs_unexport sysfs_gpio pthread)
