#ifndef MOTION_CONTROL_TRAPEZOIDALMOTIONPROFILE_H
#define MOTION_CONTROL_TRAPEZOIDALMOTIONPROFILE_H

#include <motion_control/fixed_size_stack.h>
#include <motion_control/motion_profile_1d.h>

namespace MotionControl {
    class TrapezoidalMotionProfile : public MotionProfile1D {
    FixedSizeStack<MotionProfile1D> *points;

    double vf, vi;

    double target, maxVelocity, maxAcceleration;

    double tToMaxVel, dToMaxVel;
    double tToVf, dToVf;
    double tCruising, dCruising;


    public:
        TrapezoidalMotionProfile(double target, double maxVelocity, double maxAcceleration);
        ProfilePoint1D getAtTime(double t);
        double duration();

    };
}

#endif //MOTION_CONTROL_TRAPEZOIDALMOTIONPROFILE_H
