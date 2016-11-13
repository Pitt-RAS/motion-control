#ifndef MOTION_CONTROL_RUNNER_H
#define MOTION_CONTROL_RUNNER_H

#include <motion_control/instance_linked_list.h>
#include <motion_control/runnable.h>

namespace MotionControl
{
class Runner
{
public:
    Runner();
    bool add(Runnable *runnable);
    bool remove(Runnable *runnable);
    void run();
private:
    InstanceLinkedList<Runnable*> list;
};

}

#endif
