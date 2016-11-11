#include <cstddef>
#include <motion_control/runner.h>
#include <motion_control/time.h>

namespace MotionControl
{
Runner::Runner() : list() {
}

bool Runner::add(Runnable *runnable) {
    if ( !runnable->node.in_list() )
        return list.add(&runnable->node);
    return false;
}

bool Runner::remove(Runnable *runnable) {
    return list.remove(&runnable->node);
}

void Runner::run() {
    static double lastTime = Timer::now();
    double dt = Timer::now() - lastTime;

    InstanceListNode<Runnable*> *node = list.get_root();
    while ( node != nullptr )
    {
        node->get()->run(dt);
        node = node->get_next();
    }
}

}
