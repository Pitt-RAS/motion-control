#ifndef MOTION_CONTROL_TRAPEZOIDALMOTIONPROFILE_H
#define MOTION_CONTROL_TRAPEZOIDALMOTIONPROFILE_H

#include <motion_control/fixed_size_stack.h>
#include <motion_control/motion_profile_1d.h>

namespace MotionControl {

class TrapezoidalMotionProfile : public MotionProfile1D {
public:
    TrapezoidalMotionProfile(double target, double maxVelocity,
                                                    double maxAcceleration);
    ProfilePoint1D get_at_time(double t);
    double duration();

private:
    FixedSizeStack<MotionProfile1D> *points;

    double vf, vi;

    double target, maxVelocity, maxAcceleration;

    double tToMaxVel, dToMaxVel;
    double tToVf, dToVf;
    double tCruising, dCruising;
};

}

#endif //MOTION_CONTROL_TRAPEZOIDALMOTIONPROFILE_H
