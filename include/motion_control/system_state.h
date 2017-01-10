#ifndef MOTION_CONTROL_PROFILEPOINT_H
#define MOTION_CONTROL_PROFILEPOINT_H

namespace MotionControl {

struct SystemState {
    double t;
    double pos;
    double vel;
    double acc;
};

}

#endif
