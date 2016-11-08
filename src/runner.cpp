#include <motion_control/runner.h>
#include <motion_control/time.h>

namespace MotionControl
{
Runner::Runner() : list() {
}

void Runner::add(Runnable *runnable) {
    // TODO: This currently silently fails - there should probably be some error thrown
    // because a Runnable can't be a member of two runners.
    if ( runnable->node.list == 0)
        list.add(&runnable->node);
}

void Runner::remove(Runnable *runnable) {
    list.remove(&runnable->node);
}

void Runner::run() {
    static double lastTime = Timer::now();
    double dt = Timer::now() - lastTime;

    InstanceListNode<Runnable*> *node = list.get_root();
    while ( node != 0 )
    {
        node->get()->run(dt);
        node = node->next;
    }
}

}
