#ifndef MOTION_CONTROL_RUNNABLE_H
#define MOTION_CONTROL_RUNNABLE_H

#include <motion_control/instance_linked_list.h>

namespace MotionControl
{
class Runnable
{
public:
    Runnable();
    InstanceListNode<Runnable*> node;
    virtual void run(double dt) = 0;
};
};

#endif
