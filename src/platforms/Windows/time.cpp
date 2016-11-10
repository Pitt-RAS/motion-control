#include <Windows.h>
#include <motion_control/time.h>

namespace MotionControl
{
double Timer::now()
{
    static LARGE_INTEGER start;
    static LARGE_INTEGER freq;
    static bool init = false;
    if ( !init )
    {
        init = true;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&start);
    }

    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);

    LARGE_INTEGER elapsed;
    elapsed.QuadPart = now.QuadPart - start.QuadPart;

    elapsed.QuadPart *= 1000000;
    elapsed.QuadPart /= freq.QuadPart;

    return elapsed.QuadPart / 1e6;
}

void Timer::delay(double t)
{
    Sleep(t*1000.0);
}
}
