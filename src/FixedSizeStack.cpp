#include "motion_control/FixedSizeStack.h"
#include "motion_control/MotionProfile1D.h"
#include <cstdlib>
#include <string.h>

template <class T>
MotionControl::FixedSizeStack<T>::FixedSizeStack(int maxSize) {
    this->len = 0;
    this->maxSize = maxSize;
    this->buffer = (T*)calloc(maxSize, sizeof(T));
}

template <class T>
MotionControl::FixedSizeStack<T>::~FixedSizeStack() {
    free(this->buffer);
}

template <class T>
int MotionControl::FixedSizeStack<T>::size() {
    return len;
}

template <class T>
void MotionControl::FixedSizeStack<T>::push(T* item) {
    if ( len >= maxSize)
        return;
    memcpy(&buffer[len++], item, sizeof(T));
}

template <class T>
T* MotionControl::FixedSizeStack<T>::get(int idx) {
    if ( idx < 0 || idx >= len )
        return NULL;
    return &buffer[idx];
}

// Force the compiler to generate this template for MotionControl::ProfilePoint1D 
// since it is used in tests
template class MotionControl::FixedSizeStack<MotionControl::ProfilePoint1D>;