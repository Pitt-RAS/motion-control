#ifndef MOTION_CONTROL_TIME_H
#define MOTION_CONTROL_TIME_H

namespace MotionControl {

class Timer {
public:
    static double now();
    static void delay(double t);

    Timer();
    void start();
    void stop();
    void reset();
    double get();

private:
    double startTime;
    double lastTimes;
};

}

#endif //MOTION_CONTROL_TIME_H
