#include <motion_control/time.h>

namespace MotionControl {
    Timer::Timer() {
        startTime = 0;
        lastTimes = 0;
    }

    void Timer::start() {
        startTime = Timer::now();
    }


    void Timer::stop() {
        lastTimes += Timer::now() - startTime;
        startTime = Timer::now();
    }

    void Timer::reset() {
        lastTimes = 0;
        startTime = Timer::now();
    }

    double Timer::get() {
        return (Timer::now() - startTime)+lastTimes;
    }
}

