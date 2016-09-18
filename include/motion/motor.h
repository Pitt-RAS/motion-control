#ifndef MOTION_MOTOR_H
#define MOTION_MOTOR_H

#include <cinttypes>

namespace MotionControl {

// Motor Interface
//
// A Motor's output voltage is represented by an integer ranging from
// the minimum possible voltage INT16_MIN, to zero voltage 0, to the
// maximum possible voltage INT16_MAX.
//
class Motor
{
public:
    // Returns the most recently set motor voltage.
    virtual int_fast16_t voltage() const = 0;

    // Sets the motor voltage. Returns success.
    virtual bool voltage(int_fast16_t value) = 0;
};

}

#endif
