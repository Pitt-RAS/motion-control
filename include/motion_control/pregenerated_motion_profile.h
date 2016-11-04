#ifndef MOTION_CONTROL_PREGENERATED_MOTION_H
#define MOTION_CONTROL_PREGENERATED_MOTION_H

#include <motion_control/motion_profile_1d.h>
#include <cstdlib>

namespace MotionControl {

template<const int steps>
class PregeneratedMotionProfile {
    ProfilePoint1D points[steps];
public:
    PregeneratedMotionProfile(MotionProfile1D *profile)
    {
        double dt = profile->duration()/(steps-1);
        double t = 0;
        for ( int i = 0; i < steps; i++ )
        {
            points[i] = profile->get_at_time(t);
            t += dt;
        }
    }

    int size()
    {
        return steps;
    }

    ProfilePoint1D* get(int idx) {
        if (idx < 0 || idx > steps - 1)
            return NULL;
        return &points[idx];
    }
};

}


#endif
