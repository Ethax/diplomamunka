#include "catch.hpp"
#include <utilities.hpp>
#include <map>
#include <set>

using namespace Catch;

TEST_CASE("Replace numbers to their names in string using regex")
{
    std::string test_string {
        "1, 2, Buckle my shoe;"
        "3, 4, Knock at the door;"
        "5, 6, Pick up sticks;"
        "7, 8, Lay them straight;"
        "9, 10, A big fat hen;"
    };

    test_string = util::regex_replace(test_string, std::regex("\\d+"), [](const std::string &m) {
        const std::map<std::string, std::string> names {
            {"1", "One"}, {"2", "Two"}, {"3", "Three"}, {"4", "Four"}, {"5", "Five"},
            {"6", "Six"}, {"7", "Seven"}, {"8", "Eight"}, {"9", "Nine"}, {"10", "Ten"},
        };
        return names.count(m) ? names.at(m) : m;
    });

    REQUIRE_THAT(test_string, Equals(
        "One, Two, Buckle my shoe;"
        "Three, Four, Knock at the door;"
        "Five, Six, Pick up sticks;"
        "Seven, Eight, Lay them straight;"
        "Nine, Ten, A big fat hen;"
    ));
}

TEST_CASE("Join a set of strings")
{
    const std::set<std::string> test_set {
        "Smith", "Johnson", "Williams", "Jones", "Brown",
        "Davis", "Miller", "Wilson", "Moore", "Taylor"
    };

    std::string result = util::join(test_set.begin(), test_set.end(), ", ");

    REQUIRE_THAT(result, Equals(
        "Brown, Davis, Johnson, Jones, Miller, Moore, Smith, Taylor, Williams, Wilson"
    ));
}

TEST_CASE("Transform string to lowercase")
{
    std::string test_string = "LOREM IPSUM DOLOR SIT AMET";

    REQUIRE_THAT(util::to_lower(test_string), Equals("lorem ipsum dolor sit amet"));
}

TEST_CASE("Transform string to uppercase")
{
    std::string test_string = "lorem ipsum dolor sit amet";

    REQUIRE_THAT(util::to_upper(test_string), Equals("LOREM IPSUM DOLOR SIT AMET"));
}