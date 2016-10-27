#include "gtest/gtest.h"

#include "motion_control/Time.h"
#include <math.h>

using namespace MotionControl;

static double epsilon = 0.01;
double delay = 0.1;

TEST(Timer,Now) {
    double start = Timer::now();
    Timer::delay(delay);
    EXPECT_TRUE(fabs((Timer::now()-start)-delay) < epsilon && Timer::now()-start > 0);
}

TEST(Timer,SimpleStartStop) {
    Timer t;

    t.start();
    Timer::delay(delay);
    t.stop();

    EXPECT_TRUE(fabs(t.get()-delay) < epsilon && t.get() > 0);
}


TEST(Timer, GetWhileTimerRunning) {
    Timer t;

    t.start();
    Timer::delay(delay);
    EXPECT_TRUE(fabs(t.get()-delay) < epsilon && t.get() > 0);
}


TEST(Timer,  SimpleStartStopStartStop) {
    Timer t;

    t.start();
    Timer::delay(delay);
    t.stop();
    Timer::delay(delay);
    t.start();
    Timer::delay(delay);
    t.stop();
    EXPECT_TRUE(fabs(t.get()-(delay*2)) < epsilon && t.get() > 0);
}
