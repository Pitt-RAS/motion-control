#ifndef MOTION_CONTROL_MATH_H
#define MOTION_CONTROL_MATH_H

namespace MotionControl {

template <typename type>
constexpr bool is_signed();

template <typename type>
type abs(type value);

template <typename type>
type constrain(type value, type min, type max);

template <typename type>
constexpr bool is_signed()
{
    return type(-1) < type(0);
}

template <typename type>
type abs(type value)
{
    return value >= 0 ? value : -value;
}

template <typename type>
type constrain(type value, type min, type max)
{
    if (value < min)
        return min;
    else if (value > max)
        return max;

    return value;
}

}

#endif
