#include <cinttypes>
#include <catch.hpp>
#include <motion_control/math.h>

using namespace MotionControl;

TEST_CASE("Can identify signed/unsigned", "[is_signed]")
{
    SECTION("signed")
    {
        REQUIRE(is_signed<int>());
        REQUIRE(is_signed<long>());
        REQUIRE(is_signed<int8_t>());
        REQUIRE(is_signed<int16_t>());
        REQUIRE(is_signed<int32_t>());
        REQUIRE(is_signed<int_fast8_t>());
        REQUIRE(is_signed<int_fast16_t>());
        REQUIRE(is_signed<int_fast32_t>());
    }
    SECTION("unsigned")
    {
        REQUIRE(!is_signed<unsigned int>());
        REQUIRE(!is_signed<unsigned long>());
        REQUIRE(!is_signed<uint8_t>());
        REQUIRE(!is_signed<uint16_t>());
        REQUIRE(!is_signed<uint32_t>());
        REQUIRE(!is_signed<uint_fast8_t>());
        REQUIRE(!is_signed<uint_fast16_t>());
        REQUIRE(!is_signed<uint_fast32_t>());
    }
}

TEST_CASE("Absolute value flips negative values", "[abs]")
{
    REQUIRE(abs(int8_t(-10)) == 10);
    REQUIRE(abs(int16_t(-1000)) == 1000);
    REQUIRE(abs(int32_t(-1000000000)) == 1000);
}

TEST_CASE("Absolute value does not flip non-negative values", "[abs]")
{
    REQUIRE(abs(int(0)) == 0);
    REQUIRE(abs(int8_t(10)) == 10);
    REQUIRE(abs(int16_t(1000)) == 1000);
    REQUIRE(abs(int32_t(1000000000)) == 1000);
}

TEST_CASE("Constrain does not modify value within range", "[constrain]")
{
    SECTION("int")
    {
        REQUIRE(constrain<int>(7, 5, 10) == 7);
    }

    SECTION("float")
    {
        REQUIRE(constrain<float>(7.0f, 5.0f, 10.0f) == 7.0f);
    }

    SECTION("double")
    {
        REQUIRE(constrain<double>(7.0, 5.0, 10.0) == 7.0);
    }
}

TEST_CASE("Constrain clips min", "[constrain]")
{
    SECTION("int")
    {
        REQUIRE(constrain<int>(3, 5, 10) == 5);
    }

    SECTION("float")
    {
        REQUIRE(constrain<float>(3.0f, 5.0f, 10.0f) == 5.0f);
    }

    SECTION("double")
    {
        REQUIRE(constrain<double>(3.0, 5.0, 10.0) == 5.0);
    }
}

TEST_CASE("Constrain clips max", "[constrain]")
{
    SECTION("int")
    {
        REQUIRE(constrain<int>(12, 5, 10) == 10);
    }

    SECTION("float")
    {
        REQUIRE(constrain<float>(12.0f, 5.0f, 10.0f) == 10.0f);
    }

    SECTION("double")
    {
        REQUIRE(constrain<double>(12.0, 5.0, 10.0) == 10.0);
    }
}
