#include <motion_control/runner.h>
#include <motion_control/time.h>
#include <catch.hpp>

using namespace MotionControl;

class SimpleRunnable : public Runnable
{
public:
    int count;
    double lastDt;

    SimpleRunnable() : Runnable()
    {
        count = 0;
        lastDt = 0;
    }

    void run(double dt)
    {
        lastDt = dt;
        count++;
    }
};


TEST_CASE("Runnable", "[runnable]")
{
    SECTION("runs")
    {
        Runner runner;

        SimpleRunnable a;
        SimpleRunnable b;
        SimpleRunnable c;

        REQUIRE(a.count == 0);
        REQUIRE(b.count == 0);
        REQUIRE(c.count == 0);

        runner.add(&a);
        runner.add(&b);

        runner.run();

        REQUIRE(a.count == 1);
        REQUIRE(b.count == 1);
        REQUIRE(c.count == 0);

        runner.run();

        REQUIRE(a.count == 2);
        REQUIRE(b.count == 2);
        REQUIRE(c.count == 0);
    }

    SECTION("can't add a runnable to two runners")
    {
        Runner runner1;
        Runner runner2;

        SimpleRunnable a;

        runner1.add(&a);
        runner2.add(&a);

        REQUIRE(a.count == 0);

        runner1.run();

        REQUIRE(a.count == 1);

        runner2.run();

        REQUIRE(a.count == 1);
    }

    SECTION("runnable is removable")
    {
        Runner runner;

        SimpleRunnable a;
        SimpleRunnable b;

        runner.add(&a);
        runner.add(&b);

        runner.run();

        REQUIRE(a.count == 1);
        REQUIRE(b.count == 1);

        runner.remove(&a);
        runner.run();

        REQUIRE(a.count == 1);
        REQUIRE(b.count == 2);
    }

    SECTION("dt is provided")
    {
        double epsilon = 0.01;
        double delay = 0.01;

        Runner runner;
        SimpleRunnable runnable;

        runner.add(&runnable);

        runner.run();
        Timer::delay(delay);
        runner.run();

        REQUIRE(fabs(runnable.lastDt-delay) < epsilon);

    }
}
