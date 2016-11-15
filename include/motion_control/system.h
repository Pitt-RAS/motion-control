#ifndef MOTION_CONTROL_SYSTEM_H
#define MOTION_CONTROL_SYSTEM_H

#include <motion_control/instance_linked_list.h>
#include <motion_control/controller.h>
#include <motion_control/runnable.h>
#include <motion_control/motor.h>
#include <motion_control/encoder.h>


namespace MotionControl
{
class System : public Runnable
{
public:
    System(Motor* motor, Encoder* encoder);
    void set_state(SystemState *state);

    void reset();

    bool add_controller(Controller *controller);
    bool remove_controller(Controller *controller);

    void run(double dt);
private:
    Motor* motor;
    Encoder* encoder;
    SystemState* desired;
    InstanceLinkedList<Controller*> list;
};
}

#endif
