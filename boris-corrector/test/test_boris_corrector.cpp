#include "catch.hpp"
#include <boris_corrector.h>
#include <vector>
#include <algorithm>

using namespace Catch;
using namespace diplomamunka;

TEST_CASE("Append temporary file prefix")
{
    const fs::path path = "C:\\Windows\\System32\\cmd.exe";

    const auto temp = add_temp_prefix(path);

    REQUIRE_THAT(temp.string(), Equals("C:\\Windows\\System32\\~$cmd.exe"));
}

TEST_CASE("Copy only BORIS-specific files")
{
    const std::vector<fs::path> mixed {
        "E:\\Projects\\BORIS Projects\\media\\logo.bmp",
        "E:\\Projects\\BORIS Projects\\tools\\uploader.exe",
        "E:\\Projects\\BORIS Projects\\main.BSY",
        "E:\\Projects\\BORIS Projects\\animation\\anim.FAB",
        "E:\\Projects\\BORIS Projects\\lib\\engine.sbl",
        "E:\\Projects\\BORIS Projects\\documentation\\Project Specification.docx",
        "E:\\Projects\\BORIS Projects\\media\\demo.mp4"
    };
    std::vector<fs::path> boris_only;

    std::copy_if(mixed.begin(), mixed.end(), std::back_inserter(boris_only), is_boris_file);

    REQUIRE_THAT(boris_only, Equals<fs::path>({
        "E:\\Projects\\BORIS Projects\\media\\logo.bmp",
        "E:\\Projects\\BORIS Projects\\main.BSY",
        "E:\\Projects\\BORIS Projects\\animation\\anim.FAB",
        "E:\\Projects\\BORIS Projects\\lib\\engine.sbl"
    }));
}

TEST_CASE("Replace paths in string to their counterparts.")
{
    const std::set<fs::path> new_paths {
        "E:\\Diplomamunka\\BORIS\\Emulation\\media\\logo.bmp",
        "E:\\Diplomamunka\\BORIS\\Emulation\\main.bsy",
        "E:\\Diplomamunka\\BORIS\\Emulation\\animation\\anim.fab",
        "E:\\Diplomamunka\\BORIS\\Emulation\\animation\\belt_01.bmp",
        "E:\\Diplomamunka\\BORIS\\Emulation\\animation\\belt_02.bmp",
        "E:\\Diplomamunka\\BORIS\\Emulation\\animation\\belt_03.bmp",
        "E:\\Diplomamunka\\BORIS\\Emulation\\animation\\belt_04.bmp",
        "E:\\Diplomamunka\\BORIS\\Emulation\\animation\\belt_05.bmp",
        "E:\\Diplomamunka\\BORIS\\Emulation\\lib\\engine.sbl"
    };
    boris_corrector corrector("E:\\Diplomamunka\\BORIS");

    SECTION("The whole line is a path")
    {
        struct test_pair { std::string value; std::string expected; };
        auto test = GENERATE(
            test_pair { 
                "D:\\Studies\\Diplomamunka\\Emulated System\\Emulation\\media\\logo.bmp",
                "E:\\Diplomamunka\\BORIS\\Emulation\\media\\logo.bmp"
            },
            test_pair {
                "D:\\Studies\\Diplomamunka\\Emulated System\\Emulation\\main.bsy",
                "E:\\Diplomamunka\\BORIS\\Emulation\\main.bsy"
            },
            test_pair {
                "D:\\Studies\\Diplomamunka\\Emulated System\\Emulation\\animation\\anim.fab",
                "E:\\Diplomamunka\\BORIS\\Emulation\\animation\\anim.fab"
            },
            test_pair {
                "D:\\Studies\\Diplomamunka\\Emulated System\\Emulation\\lib\\engine.sbl",
                "E:\\Diplomamunka\\BORIS\\Emulation\\lib\\engine.sbl"
            }
        );

        const auto result = corrector.correct_paths(test.value, new_paths);

        REQUIRE_THAT(result, Equals(test.expected));
    }

    SECTION("Text mixed with paths")
    {
        std::string text {
            "BMPSEQ\t0\t16777215\t2\t-1\t0\t0\tCell 2: Belt\t425\t390\t375\t80\t2\t5\t"
            "D:\\Studies\\Diplomamunka\\Emulated System\\Emulation\\animation\\belt_01.bmp\t"
            "D:\\Studies\\Diplomamunka\\Emulated System\\Emulation\\animation\\belt_02.bmp\t"
            "D:\\Studies\\Diplomamunka\\Emulated System\\Emulation\\animation\\belt_03.bmp\t"
            "D:\\Studies\\Diplomamunka\\Emulated System\\Emulation\\animation\\belt_04.bmp\t"
            "D:\\Studies\\Diplomamunka\\Emulated System\\Emulation\\animation\\belt_05.bmp\t"
            "*.bmp\t*.bmp\t*.bmp\t*.bmp\t*.bmp\t0\t0\t5\t0\tC:\\Windows\\System32\\cmd.exe"
        };
        
        text = corrector.correct_paths(text, new_paths);

        REQUIRE_THAT(text, Equals({
            "BMPSEQ\t0\t16777215\t2\t-1\t0\t0\tCell 2: Belt\t425\t390\t375\t80\t2\t5\t"
            "E:\\Diplomamunka\\BORIS\\Emulation\\animation\\belt_01.bmp\t"
            "E:\\Diplomamunka\\BORIS\\Emulation\\animation\\belt_02.bmp\t"
            "E:\\Diplomamunka\\BORIS\\Emulation\\animation\\belt_03.bmp\t"
            "E:\\Diplomamunka\\BORIS\\Emulation\\animation\\belt_04.bmp\t"
            "E:\\Diplomamunka\\BORIS\\Emulation\\animation\\belt_05.bmp\t"
            "*.bmp\t*.bmp\t*.bmp\t*.bmp\t*.bmp\t0\t0\t5\t0\tC:\\Windows\\System32\\cmd.exe"
        }));
    }
}