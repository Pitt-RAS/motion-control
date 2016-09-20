#ifndef SYSFS_GPIO_H
#define SYSFS_GPIO_H

#include <thread>
#include <cstdlib>
#include <cinttypes>

#define SYSFS_GPIO_SYSFS_PATH "/sys/class/gpio"
#define SYSFS_GPIO_LARGEST_PATH SYSFS_GPIO_SYSFS_PATH "/gpioXXXXX/direction"
#define SYSFS_GPIO_PATH_LENGTH sizeof(SYSFS_GPIO_LARGEST_PATH)

namespace SysfsGPIO {

enum class Direction { In, Out };
enum class Edge { None, Rising, Falling, Both };

// Exports the numbered GPIO to userspace. Returns success.
bool export_gpio(uint16_t number);

// Reverses the effect of exporting to userspace. Returns success.
bool unexport_gpio(uint16_t number);

// Wrapper around a Linux sysfs GPIO
class GPIO
{
public:
    GPIO(uint16_t number);
    ~GPIO();

    // Returns the value. Returns false on failure.
    bool value();

    // Sets the value. Returns success.
    bool value(bool value);

    // Returns the direction. Returns In on failure.
    Direction direction();

    // Sets the direction. Returns success.
    bool direction(Direction value);

    // Returns the interrupt edge. Returns None on failure.
    Edge edge();

    // Sets the interrupt edge. Returns success.
    bool edge(Edge value);

    // Waits indefinitely for an interrupt to occur.
    bool wait();

private:
    const int number;

    char value_path[SYSFS_GPIO_PATH_LENGTH];
    char direction_path[SYSFS_GPIO_PATH_LENGTH];
    char edge_path[SYSFS_GPIO_PATH_LENGTH];

    int value_read_fd;
    int value_write_fd;
    int value_poll_fd;

    void build_path(char *destination, const char *basename);
};

// Software PWM Generator
//
// Uses a software loop in a dedicated thread to generate a PWM signal
// on the given GPIO.
//
class SoftwarePWMGenerator
{
public:
    SoftwarePWMGenerator(GPIO &gpio);
    ~SoftwarePWMGenerator();

    uint_fast16_t duty() const;
    bool duty(uint_fast16_t value);

    uint_fast32_t frequency() const;
    bool frequency(uint_fast32_t value);

private:
    GPIO &gpio;

    bool running = true;
    std::thread thread = std::thread(&SoftwarePWMGenerator::generate, this);

    volatile uint_fast32_t period = 1e6;
    volatile uint_fast32_t on_time = 0;
    volatile uint_fast32_t off_time = period;

    void generate();
};

// Interrupt Listener
//
// Uses a software loop in a dedicated thread to listen for interrupts
// on the given GPIO. Each time an interrupt occurs, the given routine
// is called.
//
class InterruptListener
{
public:
    // An interrupt routine has no parameters and returns nothing.
    typedef void (*InterruptRoutine)(void *data);

    InterruptListener(GPIO &gpio, InterruptRoutine routine, void *data);
    ~InterruptListener();

private:
    GPIO &gpio;

    bool running = true;
    InterruptRoutine routine;
    void *data;
    std::thread thread = std::thread(&InterruptListener::listen, this);

    void listen();
};

}

#endif
