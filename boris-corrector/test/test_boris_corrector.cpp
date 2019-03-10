#include "catch.hpp"
#include <boris_corrector.h>
#include <vector>
#include <algorithm>

using namespace Catch;
using namespace diplomamunka;

TEST_CASE("Copy only BORIS-specific files")
{
    std::vector<fs::path> mixed {
        "E:/Projects/BORIS Projects/media/logo.bmp",
        "E:/Projects/BORIS Projects/tools/uploader.exe",
        "E:/Projects/BORIS Projects/main.bsy",
        "E:/Projects/BORIS Projects/animation/animation.fab",
        "E:/Projects/BORIS Projects/lib/engine.sbl",
        "E:/Projects/BORIS Projects/documentation/Project Specification.docx",
        "E:/Projects/BORIS Projects/media/demo.mp4"
    };
    std::vector<fs::path> boris_only;

    std::copy_if(mixed.begin(), mixed.end(), std::back_inserter(boris_only), is_boris_file);

    REQUIRE_THAT(boris_only, Equals<fs::path>({
        "E:/Projects/BORIS Projects/media/logo.bmp",
        "E:/Projects/BORIS Projects/main.bsy",
        "E:/Projects/BORIS Projects/animation/animation.fab",
        "E:/Projects/BORIS Projects/lib/engine.sbl"
    }));
}