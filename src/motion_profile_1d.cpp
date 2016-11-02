#include <motion_control/motion_profile_1d.h>
#include <stdlib.h>

namespace MotionControl {

MotionProfile1D::MotionProfile1D()
{
    points = NULL;
}

void MotionProfile1D::generate(double dt)
{
    int steps = duration()/dt;

    if ( points != NULL )
        delete points;

    points = new FixedSizeStack<ProfilePoint1D>(steps);

    for ( int i = 0; i < steps; i++ ) {
        ProfilePoint1D p = get_at_time(i * dt);
        points->push(&p);
    }
}

ProfilePoint1D MotionProfile1D::get_at_index(int idx)
{
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

int MotionProfile1D::steps()
{
    if ( points == NULL )
        return 0;
    return points->size();
}

bool MotionProfile1D::is_pregenerated()
{
    return points != NULL;
}

}
