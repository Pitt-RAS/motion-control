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

        InstanceListNode<Controller*> *node = list.get_root();
        while ( node != nullptr )
        {
            output += node->get()->calculate(dt, current, desired);
            node = node->get_next();
        }

        motor->voltage(output);
    }
}

void System::reset() {
    InstanceListNode<Controller*> *node = list.get_root();
    while ( node != nullptr )
    {
        node->get()->reset();
        node = node->get_next();
    }
}
}
