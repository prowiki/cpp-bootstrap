#include "common_utils/math_utils.hh"
#include <catch.hpp>

TEST_CASE("Test add two integers")
{
    REQUIRE(add(1, 2) == 3);
}

TEST_CASE("Test add two integers - require false")
{
    int result = add(1, 2);
    REQUIRE(result == 4);
    CAPTURE(result);
}
