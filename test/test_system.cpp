#include <motion_control/motion_control.h>
#include <catch.hpp>

using namespace MotionControl;

// A simple actuator (motor encoder pair)
class SimpleActuator : public Encoder, public Motor
{
public:

    SimpleActuator() : val(0)
    {}

    float voltage() const
    {
        return val;
    }

    bool voltage(float value)
    {
        val = value;
        return true;
    }

    bool count(int_fast32_t count)
    {
        pos = count;
        return true;
    }

    int_fast32_t count() const
    {
        return pos;
    }

private:
    float val;
    int_fast32_t pos;
};

// Simple controller that sums the desired position and current tick count
class SimpleController : public Controller
{
public:
    SimpleController()
    {
    }

    float calculate(double dt, int_fast32_t current, SystemState& desired)
    {
        // (dt/dt) avoids an unused parameter error from Wpedantic + Werror
        return static_cast<float>(desired.pos) + static_cast<float>(current) * static_cast<float>(dt/dt);
    }

    void reset()
    {}
};


TEST_CASE("System", "[system]")
{
    /*
     * Constructs a system using a dummy motor, encoder, and controller
     * Runs one loop of the system
     */
    SECTION("run of system completes")
    {
        // Create a SystemState with pos=10
        SystemState desired = { 0, 10, 0, 0 };

        // Setup the actuator and set the count to 5
        SimpleActuator actuator;
        actuator.count(5);

        // Create the system with our test actuator as the encoder and motor
        System actuatorSystem(actuator, actuator);

        // Set our desired state for the system
        // (this is provided to each controller)
        actuatorSystem.set_state(desired);

        // Setup the controller
        // This controller sums the desired position
        // with the current encoder count
        SimpleController controller;

        // Add this controller to the system
        actuatorSystem.add_controller(controller);

        // Run this system for one loop (dt=1, it is not used by this test)
        actuatorSystem.run(1);

        REQUIRE(actuator.voltage() == desired.pos+actuator.count());
    }
}
