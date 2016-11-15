#ifndef MOTION_CONTROL_CONTROLLER_H
#define MOTION_CONTROL_CONTROLLER_H

#include <motion_control/controller.h>
#include <motion_control/system_state.h>
#include <motion_control/instance_linked_list.h>

namespace MotionControl
{
class Controller
{
public:
    Controller();
    virtual double calculate(double dt, SystemState *current, SystemState *desired) = 0;
    virtual void reset() = 0;
    InstanceListNode<Controller*> node;
};
}

#endif
