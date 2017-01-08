#include <motion_control/time.h>
#include <math.h>
#include <catch.hpp>

using namespace MotionControl;


TEST_CASE("Timer", "[timer]")
{
    double epsilon = 0.02;
    double delay = 0.2;

    SECTION("now() and delay()")
    {
        double start = Timer::now();
        Timer::delay(delay);

        REQUIRE((fabs((Timer::now()-start)-delay) < epsilon && Timer::now()-start > 0));
    }

    SECTION("get after stop")
    {
        Timer t;

        t.start();
        Timer::delay(delay);
        t.stop();

        REQUIRE((fabs(t.get()-delay) < epsilon && t.get() > 0));
    }

    SECTION("get without stop")
    {
        Timer t;

        t.start();
        Timer::delay(delay);

        REQUIRE((fabs(t.get()-delay) < epsilon && t.get() > 0));
    }

    SECTION("does not increment while stopped")
    {
        Timer t;

        t.start();
        Timer::delay(delay);
        t.stop();
        Timer::delay(delay);
        t.start();
        Timer::delay(delay);
        t.stop();

        REQUIRE((fabs(t.get()-(delay*2)) < epsilon && t.get() > 0));
    }
}
