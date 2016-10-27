#include "gtest/gtest.h"
#include "motion_control/FixedSizeStack.h"
#include "motion_control/ProfilePoint.h"

MotionControl::ProfilePoint1D* nullPoint = (MotionControl::ProfilePoint1D*)NULL;

TEST(FixedSizeStack, AddAndGet) {
    MotionControl::ProfilePoint1D a = { 1,2 };
    MotionControl::ProfilePoint1D b = { 4,5 };

    MotionControl::FixedSizeStack<MotionControl::ProfilePoint1D> stack(2);
    stack.push(&a);
    stack.push(&b);


    ASSERT_EQ(stack.size(), 2);

    MotionControl::ProfilePoint1D ret = *stack.get(0);
    ASSERT_EQ(ret.pos, a.pos);
    ASSERT_EQ(ret.vel, a.vel);

    ret = *stack.get(1);
    ASSERT_EQ(ret.pos, b.pos);
    ASSERT_EQ(ret.vel, b.vel);
}

TEST(FixedSizeStack, EmptyTest) {
    MotionControl::FixedSizeStack<MotionControl::ProfilePoint1D> stack(2);


    ASSERT_EQ(stack.size(), 0);

    MotionControl::ProfilePoint1D* ret;


    ret = stack.get(0);
    ASSERT_EQ(ret, nullPoint);

    ret = stack.get(1);
    ASSERT_EQ(ret, nullPoint);

    ret = stack.get(2);
    ASSERT_EQ(ret, nullPoint);
}

TEST(FixedSizeStack, Overfill) {
    MotionControl::ProfilePoint1D a = { 1,2 };

    MotionControl::FixedSizeStack<MotionControl::ProfilePoint1D> stack(2);
    stack.push(&a);
    stack.push(&a);
    stack.push(&a);
    ASSERT_EQ(stack.size(), 2);

    MotionControl::ProfilePoint1D* ret;

    ret = stack.get(0);
    ASSERT_NE(ret, nullPoint);

    ret = stack.get(1);
    ASSERT_NE(ret, nullPoint);

    ret = stack.get(2);
    ASSERT_EQ(ret, nullPoint);

    ret = stack.get(-1);
    ASSERT_EQ(ret, nullPoint);
}