#include <motion_control/fixed_size_stack.h>
#include <motion_control/motion_profile_1d.h>
#include <cstdlib>
#include <string.h>

namespace MotionControl {
    template <class T> FixedSizeStack<T>::FixedSizeStack(int maxSize) {
        this->len = 0;
        this->maxSize = maxSize;
        this->buffer = (T*)calloc(maxSize, sizeof(T));
    }

    template <class T> FixedSizeStack<T>::~FixedSizeStack() {
        free(this->buffer);
    }

    template <class T> int FixedSizeStack<T>::size() {
        return len;
    }

    template <class T> void FixedSizeStack<T>::push(T* item) {
        if ( len >= maxSize)
        return;
        memcpy(&buffer[len++], item, sizeof(T));
    }

    template <class T> T* FixedSizeStack<T>::get(int idx) {
        if ( idx < 0 || idx >= len )
        return NULL;
        return &buffer[idx];
    }

    // Force the compiler to generate this template for MotionControl::ProfilePoint1D
    template class FixedSizeStack<ProfilePoint1D>;
}
