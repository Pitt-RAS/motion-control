#ifndef MOTION_ENCODER_H
#define MOTION_ENCODER_H

#include <cinttypes>
#include <motion_control/system_state.h>

namespace MotionControl {

// Encoder Interface
//
// An encoder's position is represented by its count, which is the
// displacement from some arbitrary zero position, measured in
// discrete encoder ticks.
//
// The count overflow behavior is undefined.
//
class Encoder
{
public:
    // Returns the count.
    virtual int_fast32_t count() const = 0;

    // Sets the count to an arbitrary value. Returns success.
    virtual bool count(int_fast32_t value) = 0;
};

}

#endif
