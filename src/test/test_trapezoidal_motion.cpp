#include "gtest/gtest.h"
#include "motion_control/motion_control.h"
#include <math.h>

using namespace MotionControl;

// dt Used for numerical integration
double dt = 0.01;

double target = 100;
double maxVelocity = 10;
double maxAcceleration = 5;

static double epsilon = 0.001;


// Check if the last point in the profile is at our target
TEST(TrapezoidalMotionProfile, GetsToTarget) {
    TrapezoidalMotionProfile profile(target, maxVelocity, maxAcceleration);

    ProfilePoint1D last = profile.getAtTime(profile.duration());

    ASSERT_GT(profile.duration(), 0);
    ASSERT_EQ(last.pos, 100);
}

// Integrate velocity and see if we end up at the target
TEST(TrapezoidalMotionProfile, OnTheFlyMathCheck) {
    TrapezoidalMotionProfile profile(target, maxVelocity, maxAcceleration);

    int steps = profile.duration()/dt;

    ASSERT_NE(steps, 0);

    double posFromVel = 0;
    for ( int i = 0; i < steps; i++ ) {
        double t = i * dt;
        ProfilePoint1D p = profile.getAtTime(t);

        posFromVel += p.vel * dt;
    }


    ASSERT_TRUE(fabs(target-posFromVel) < epsilon);
}
