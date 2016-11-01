#ifndef MOTION_CONTROL_TIME_H
#define MOTION_CONTROL_TIME_H

namespace MotionControl {
    class Timer {
        double startTime;
        double lastTimes;
        public:
            static double now();
            static void delay(double t);

            Timer();
            void start();
            void stop();
            void reset();
            double get();
    };
}

#endif //MOTION_CONTROL_TIME_H
