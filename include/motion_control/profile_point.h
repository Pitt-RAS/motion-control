#ifndef MOTION_CONTROL_PROFILEPOINT_H
#define MOTION_CONTROL_PROFILEPOINT_H

namespace MotionControl {

struct ProfilePoint1D {
    double t;
    double pos;
    double vel;
};

struct ProfilePoint2D {
    double t;
    ProfilePoint1D left;
    ProfilePoint1D right;
    double theta;
};

}

#endif
