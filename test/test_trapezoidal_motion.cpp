#include <catch.hpp>
#include <motion_control/motion_control.h>

using namespace MotionControl;

TEST_CASE("TrapezoidalMotionProfile", "[trapezoidal]")
{
    // dt Used for numerical integration
    double dt = 0.01;

    double target = 100;
    double maxVelocity = 10;
    double maxAcceleration = 5;

    double epsilon = 0.001;

    SECTION("integrate velocity and see if we end up at the target")
    {
        TrapezoidalMotionProfile profile(target, maxVelocity, maxAcceleration);

        int steps = static_cast<int>(profile.duration()/dt);

        REQUIRE(steps != 0);

        double posFromVel = 0;
        for ( int i = 0; i < steps; i++ ) {
            double t = i * dt;
            SystemState p = profile.get_at_time(t);

            posFromVel += p.vel * dt;
        }

        REQUIRE(fabs(target-posFromVel) < epsilon);
    }

    SECTION("check if the last point in the profile is at our target")
    {
        TrapezoidalMotionProfile profile(target, maxVelocity, maxAcceleration);

        SystemState last = profile.get_at_time(profile.duration());

        REQUIRE(profile.duration() != 0);
        REQUIRE(last.pos == 100);
    }

    SECTION("pregenerate profile")
    {
        TrapezoidalMotionProfile profile(target, maxVelocity, maxAcceleration);
        PregeneratedMotionProfile<100> profile_table(&profile);

        REQUIRE(profile_table.size() == 100);
        REQUIRE(profile_table.get(99)->pos == target);
        REQUIRE(profile_table.get(0)->pos == 0);
    }

    SECTION("integrate position from velocity in triangular case ")
    {
        TrapezoidalMotionProfile profile(5, 10, 10);

        int steps = static_cast<int>(profile.duration()/dt);
        REQUIRE(steps != 0);

        double posFromVel = 0;
        for ( int i = 0; i < steps; i++ ) {
            double t = i * dt;
            SystemState p = profile.get_at_time(t);
            posFromVel += p.vel * dt;
        }

        REQUIRE(fabs(5-posFromVel) < epsilon);
    }

}
