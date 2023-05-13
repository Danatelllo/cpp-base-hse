#include <catch.hpp>
#include <palindrome.h>

TEST_CASE("IsPalindrome") {
    REQUIRE(IsPalindrome("ab ba"));

    REQUIRE(!IsPalindrome("qwerty"));
}
