#include <motion_control/trapezoidal_motion_profile.h>
#include <math.h>

namespace MotionControl {

TrapezoidalMotionProfile::TrapezoidalMotionProfile
    (double target, double maxVelocity, double maxAcceleration)
{
    vi = 0;
    vf = 0;

    this->target = target;
    this->maxVelocity = maxVelocity;
    this->maxAcceleration = maxAcceleration;

    tToMaxVel = (maxVelocity-vi)/maxAcceleration;
    dToMaxVel = 0.5*maxAcceleration*(tToMaxVel*tToMaxVel);

    tToVf = (maxVelocity-vf)/maxAcceleration;
    dToVf = 0.5*maxAcceleration*(tToVf*tToVf);

    dCruising = target-dToMaxVel-dToVf;
    tCruising = dCruising / maxVelocity;

    if ( fabs(target) - fabs(dToMaxVel) - fabs(dToVf) < 0 ) {
        // Make triangular, can't achieve maxVelocity
        tToMaxVel = tToVf = fabs(sqrt(2.0 * maxAcceleration * (target / 2.0)) / maxAcceleration);
        tCruising = dCruising = 0;
        dToMaxVel = dToVf = target / 2.0;
        this->maxVelocity = maxAcceleration*tToMaxVel;
    }
}

SystemState TrapezoidalMotionProfile::get_at_time(double t)
{
    SystemState point;

    point.t = t;

    if ( t > tToMaxVel+tToVf+tCruising )
    {
        t = tToMaxVel+tToVf+tCruising;
    }
    if ( t <= tToMaxVel && tToMaxVel != 0 )
    {
        point.pos = (0.5) * maxAcceleration * (t*t);
        point.vel = (maxAcceleration * t) + vi;
        point.acc = maxAcceleration;
    }
    else if ( t < (tToMaxVel+tCruising) )
    {
        double i = t-tToMaxVel;
        point.pos = dToMaxVel + (maxVelocity * i);
        point.vel = maxVelocity;
        point.acc = 0;
    }
    else if ( t <= (tToMaxVel+tToVf+tCruising) )
    {
        double i = t-tToMaxVel-tCruising;
        point.pos = (dCruising + dToMaxVel) + (maxVelocity * i)
                                            + (0.5) * -maxAcceleration * (i*i);
        point.vel = maxVelocity + ((-maxAcceleration) * i);
        point.acc = -maxAcceleration;
    }

    if ( t == tToMaxVel+tToVf+tCruising )
    {
        point.pos = target;
        point.vel = vf;
        if ( vf == 0 )
            point.acc = 0;
        else
            point.acc = -maxAcceleration;
    }

    return point;
}

double TrapezoidalMotionProfile::duration()
{
    return tToMaxVel+tToVf+tCruising;
}

}
