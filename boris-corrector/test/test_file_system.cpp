#include "catch.hpp"
#include <file_system.hpp>

using namespace Catch;

TEST_CASE("Create relative path from absolute path")
{
    fs::path path = "C:/Windows/System32/cmd.exe";

    auto relative_path = fs::relative(path, "C:/Windows");

    REQUIRE(relative_path == "System32/cmd.exe");
}

TEST_CASE("Test if an absolute path ends with a given relative path")
{
    fs::path path = "C:/Windows/System32/cmd.exe";

    REQUIRE(fs::ends_with(path, "System32/cmd.exe"));
}
