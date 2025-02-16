#include "lib.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Behold", "The Truth:") { REQUIRE(lib::return_true()); }
