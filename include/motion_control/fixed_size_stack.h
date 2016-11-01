#ifndef MOTION_CONTROL_FIXEDSIZESTACK_H
#define MOTION_CONTROL_FIXEDSIZESTACK_H

namespace MotionControl {
template<class T>
class FixedSizeStack {
int len;
int maxSize;
T *buffer;
public:
FixedSizeStack(int maxSize);

~FixedSizeStack();

T* get(int idx);

void push(T* item);

int size();
};
}


#endif //MOTION_CONTROL_FIXEDSIZESTACK_H
