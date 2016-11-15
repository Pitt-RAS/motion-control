#include <motion_control/system.h>

namespace MotionControl
{
bool System::add_controller(Controller *controller) {
    if ( !controller->node.in_list() )
        return list.add(&controller->node);
    return false;
}

bool System::remove_controller(Controller *controller) {
    return list.remove(&controller->node);
}

void System::set_state(SystemState *state) {
    desired = state;
}

void System::run(double dt) {
    if ( desired != nullptr ) {
        double output = 0;
        SystemState* current = encoder->get_state();

        InstanceListNode<Controller*> *pos = list.get_root();
        while ( pos != nullptr )
        {
            output += pos->get()->calculate(dt, current, desired);
            pos = pos->get_next();
        }

        motor->voltage(output);
    }
}

void System::reset() {
    InstanceListNode<Controller*> *pos = list.get_root();
    while ( pos != nullptr )
    {
        pos->get()->reset();
        pos = pos->get_next();
    }
}
}
