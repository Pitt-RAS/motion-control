#ifndef MOTION_CONTROL_TRAPEZOIDALMOTIONPROFILE_H
#define MOTION_CONTROL_TRAPEZOIDALMOTIONPROFILE_H

#include <motion_control/motion_profile_1d.h>

namespace MotionControl {

class TrapezoidalMotionProfile : public MotionProfile1D {
public:
    TrapezoidalMotionProfile(double target, double maxVelocity,
                                                    double maxAcceleration);
    virtual SystemState get_at_time(double t);
    virtual double duration();

private:
    double vf, vi;

    double target, maxVelocity, maxAcceleration;

    double tToMaxVel, dToMaxVel;
    double tToVf, dToVf;
    double tCruising, dCruising;
};

}

#endif //MOTION_CONTROL_TRAPEZOIDALMOTIONPROFILE_H
