#include "motion_control/MotionProfile1D.h"
#include <stdlib.h>

MotionControl::MotionProfile1D::MotionProfile1D() {
    points = NULL;
}

void MotionControl::MotionProfile1D::generate(double dt) {
    int steps = duration()/dt;

    if ( points != NULL )
        delete points;

    points = new MotionControl::FixedSizeStack<ProfilePoint1D>(steps);

    for ( int i = 0; i < steps; i++ ) {
        ProfilePoint1D p = getAtTime(i * dt);
        points->push(&p);
    }
}

MotionControl::ProfilePoint1D MotionControl::MotionProfile1D::getAtIndex(int idx) {
    if ( points == NULL || points->size() == 0 ) {
        ProfilePoint1D p = {0,0,0};
        return p;
    }

    if ( idx < 0 )
        return *points->get(0);

    if ( idx > points->size() )
        return *points->get(points->size()-1);

    return *points->get(idx);
}