#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <poll.h>
#include <sysfs_gpio.h>
#include <motion_control/math.h>

namespace SysfsGPIO {

bool export_gpio(uint16_t number)
{
    int status;
    char buffer[6];
    int export_fd;

    sprintf(buffer, "%" PRIu16 "\n", number);

    export_fd = open(SYSFS_GPIO_SYSFS_PATH "/export", O_WRONLY);

    if (export_fd == -1)
        return false;

    status = write(export_fd, buffer, strlen(buffer));

    if ((size_t) status != strlen(buffer))
        return false;

    return true;
}

bool unexport_gpio(uint16_t number)
{
    int status;
    char buffer[6];
    int unexport_fd;

    sprintf(buffer, "%" PRIu16 "\n", number);

    unexport_fd = open(SYSFS_GPIO_SYSFS_PATH "/unexport", O_WRONLY);

    if (unexport_fd == -1)
        return false;

    status = write(unexport_fd, buffer, strlen(buffer));

    if ((size_t) status != strlen(buffer))
        return false;

    return true;
}

GPIO::GPIO(uint16_t number) : number(number)
{
    build_path(value_path, "value");
    build_path(direction_path, "direction");
    build_path(edge_path, "edge");

    value_read_fd = open(value_path, O_RDONLY);
    value_write_fd = open(value_path, O_WRONLY);
    value_poll_fd = open(value_path, O_RDONLY);
}

GPIO::~GPIO()
{
    close(value_read_fd);
    close(value_write_fd);
    close(value_poll_fd);
}

bool GPIO::value()
{
    int status;
    char buffer[1];

    status = read(value_read_fd, buffer, 1);

    // if failed, try reopening
    if (status != 1) {
        close(value_read_fd);
        value_read_fd = open(value_path, O_RDONLY);

        status = read(value_read_fd, buffer, 1);

        if (status != 1) {
            value_read_fd = -1;
            return false;
        }
    }

    status = lseek(value_read_fd, 0, SEEK_SET);

    if (status == -1) {
        value_read_fd = -1;
        return false;
    }

    return buffer[0] == '1';
}

bool GPIO::value(bool value)
{
    int status;

    if (value)
        status = write(value_write_fd, "1", 1);
    else
        status = write(value_write_fd, "0", 1);

    // if failed, try reopening
    if (status != 1) {
        close(value_write_fd);
        value_write_fd = open(value_path, O_WRONLY);

        if (value)
            status = write(value_write_fd, "1", 1);
        else
            status = write(value_write_fd, "0", 1);

        if (status != 1) {
            value_write_fd = -1;
            return false;
        }
    }

    status = lseek(value_write_fd, 0, SEEK_SET);

    if (status == -1)
        return false;

    return true;
}

Direction GPIO::direction()
{
    int status;
    char buffer[1];
    int direction_fd;

    direction_fd = open(direction_path, O_RDONLY);

    if (direction_fd == -1)
        return Direction::In;

    status = read(direction_fd, buffer, 1);

    if (status != 1)
        return Direction::In;

    Direction value;

    switch (buffer[0]) {
    case 'i':
        value = Direction::In;
        break;
    case 'o':
        value = Direction::Out;
        break;
    default:
        return Direction::In;
        break;
    }

    close(direction_fd);

    return value;
}

bool GPIO::direction(Direction value)
{
    int status;
    int direction_fd;
    int size;

    direction_fd = open(direction_path, O_WRONLY);

    if (direction_fd == -1)
        return false;

    switch (value) {
    case Direction::In:
        size = sizeof("in\n");
        status = write(direction_fd, "in\n", size);
        break;
    case Direction::Out:
        size = sizeof("out\n");
        status = write(direction_fd, "out\n", size);
        break;
    }

    if (status != size)
        return false;

    return true;
}

Edge GPIO::edge()
{
    int status;
    char buffer[1];
    int edge_fd;

    edge_fd = open(edge_path, O_RDONLY);

    if (edge_fd == -1)
        return Edge::None;

    status = read(edge_fd, buffer, 1);

    if (status != 1)
        return Edge::None;

    Edge value;

    switch (buffer[0]) {
    case 'n':
        value = Edge::None;
        break;
    case 'r':
        value = Edge::Rising;
        break;
    case 'f':
        value = Edge::Falling;
        break;
    case 'b':
        value = Edge::Both;
        break;
    }

    close(edge_fd);

    return value;
}

bool GPIO::edge(Edge value)
{
    int status;
    int edge_fd;
    int size;

    edge_fd = open(edge_path, O_WRONLY);

    if (edge_fd == -1)
        return false;

    switch (value) {
    case Edge::None:
        size = sizeof("none\n");
        status = write(edge_fd, "none\n", size);
        break;
    case Edge::Rising:
        size = sizeof("rising\n");
        status = write(edge_fd, "rising\n", size);
        break;
    case Edge::Falling:
        size = sizeof("falling\n");
        status = write(edge_fd, "falling\n", size);
        break;
    case Edge::Both:
        size = sizeof("both\n");
        status = write(edge_fd, "both\n", size);
        break;
    }

    if (status != size)
        return false;

    return true;
}

bool GPIO::wait()
{
    int status;
    char buffer[1];
    struct pollfd fds[1];

    fds[0].fd = value_poll_fd;
    fds[0].events = POLLPRI | POLLERR;

    read(value_poll_fd, buffer, 1);
    lseek(value_poll_fd, 0, SEEK_SET);
    status = poll(fds, 1, -1);

    // if failed, try reopening
    if (status != 1) {
        close(value_poll_fd);
        value_read_fd = open(value_path, O_RDONLY);

        read(value_poll_fd, buffer, 1);
        lseek(value_poll_fd, 0, SEEK_SET);
        status = poll(fds, 1, -1);

        if (status != 1) {
            value_poll_fd = -1;
            return false;
        }
    }

    return true;
}

void GPIO::build_path(char *destination, const char *basename)
{
    sprintf(destination, SYSFS_GPIO_SYSFS_PATH "/gpio%" PRIu16 "/%s",
                                                            number, basename);
}

SoftwarePWMGenerator::SoftwarePWMGenerator(GPIO &gpio) : gpio(gpio)
{}

SoftwarePWMGenerator::~SoftwarePWMGenerator()
{
    running = false;
    thread.join();
}

float SoftwarePWMGenerator::duty() const
{
    float converted = on_time;
    converted /= period;

    return converted;
}

bool SoftwarePWMGenerator::duty(float value)
{
    if (MotionControl::constrain(value, 0.0f, 1.0f) != value)
        return false;

    on_time = value * period;
    off_time = period - on_time;

    return true;
}

uint_fast32_t SoftwarePWMGenerator::frequency() const
{
    uint_fast32_t converted = 1e9;
    converted /= period;

    return converted;
}

bool SoftwarePWMGenerator::frequency(uint_fast32_t value)
{
    if (value == 0)
        return false;

    uint_fast32_t converted = 1e9;
    converted /= value;

    uint_fast16_t saved_duty = duty();
    period = converted;
    duty(saved_duty);

    return true;
}

void SoftwarePWMGenerator::generate()
{
	while (running) {
		struct timespec on_ts;
		on_ts.tv_sec = 0;
		on_ts.tv_nsec = on_time;

		struct timespec off_ts;
		off_ts.tv_sec = 0;
		off_ts.tv_nsec = off_time;

		if (on_ts.tv_nsec != 0) {
			gpio.value(true);
			nanosleep(&on_ts, NULL);
		}

		if (off_ts.tv_nsec != 0) {
			gpio.value(false);
			nanosleep(&off_ts, NULL);
		}
	}
}

InterruptListener::InterruptListener(GPIO &gpio,
                                        InterruptRoutine routine, void *data) :
    gpio(gpio), routine(routine), data(data)
{}

InterruptListener::~InterruptListener()
{
    running = false;
    thread.join();
}

void InterruptListener::listen()
{
    while (running) {
        gpio.wait();
        routine(data);
    }
}

}
