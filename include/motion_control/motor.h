#ifndef MOTION_MOTOR_H
#define MOTION_MOTOR_H

namespace MotionControl {

// Motor Interface
//
// A Motor's output voltage is represented by an integer ranging from
// the minimum possible voltage -1.0, to zero voltage 0.0, to the
// maximum possible voltage +1.0.
//
class Motor
{
public:
    // Returns the most recently set motor voltage.
    virtual float voltage() const = 0;

    // Sets the motor voltage. Returns success.
    virtual bool voltage(float value) = 0;
};

}

#endif
