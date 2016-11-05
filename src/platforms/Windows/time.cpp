#include <Windows.h>
#include <motion_control/time.h>

namespace MotionControl
{
double Timer::now()
{
    return (double)GetTickCount() / 1000.0;
}

void Timer::delay(double t)
{
    Sleep(t*1000.0);
}
}
