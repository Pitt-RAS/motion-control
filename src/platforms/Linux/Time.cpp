#include "../../Time.h"
#include <sys/time.h>
#include <math.h>
#include <unistd.h>

double MotionControl::Timer::now() {
    static timeval time;
    gettimeofday(&time, NULL);

    return (double)time.tv_sec + (double)time.tv_usec*(double)1e-6;
}


void MotionControl::Timer::delay(double t) {
    unsigned long wait = floor(t*1000000);
    usleep(wait);
}
