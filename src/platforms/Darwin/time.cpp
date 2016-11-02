#include <motion_control/time.h>
#include <sys/time.h>
#include <math.h>
#include <unistd.h>


namespace MotionControl {

double Timer::now()
{
    static timeval time;
    gettimeofday(&time, NULL);

    return (double)time.tv_sec + (double)time.tv_usec*(double)1e-6;
}

void Timer::delay(double t)
{
    unsigned long wait = floor(t*1000000);
    usleep(wait);
}

}
