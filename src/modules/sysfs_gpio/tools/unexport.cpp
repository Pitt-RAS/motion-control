#include <iostream>
#include <cinttypes>
#include <sysfs_gpio.h>

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; i++) {
        intmax_t number = strtoimax(argv[i], NULL, 10);

        if (!SysfsGPIO::unexport_gpio(number))
            std::cerr << "Unexport " << number << " failed" << std::endl;
    }
}
