#include "catch.hpp"
#include <boris_corrector.h>
#include <vector>
#include <algorithm>

using namespace Catch;
using namespace diplomamunka;

TEST_CASE("Copy only BORIS-specific files")
{
    std::vector<fs::path> mixed {
        "E:\\Projects\\BORIS Projects\\media\\logo.bmp",
        "E:\\Projects\\BORIS Projects\\tools\\uploader.exe",
        "E:\\Projects\\BORIS Projects\\main.bsy",
        "E:\\Projects\\BORIS Projects\\animation\\anim.fab",
        "E:\\Projects\\BORIS Projects\\lib\\engine.sbl",
        "E:\\Projects\\BORIS Projects\\documentation\\Project Specification.docx",
        "E:\\Projects\\BORIS Projects\\media\\demo.mp4"
    };
    std::vector<fs::path> boris_only;

    std::copy_if(mixed.begin(), mixed.end(), std::back_inserter(boris_only), is_boris_file);

    REQUIRE_THAT(boris_only, Equals<fs::path>({
        "E:\\Projects\\BORIS Projects\\media\\logo.bmp",
        "E:\\Projects\\BORIS Projects\\main.bsy",
        "E:\\Projects\\BORIS Projects\\animation\\anim.fab",
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
        SECTION("Path to a BMP file.")
        {
            std::string test {
                "D:\\Studies\\Diplomamunka\\Emulated System\\Emulation\\media\\logo.bmp"
            };
            test = corrector.correct_paths(test, new_paths);
            REQUIRE_THAT(test, Equals("E:\\Diplomamunka\\BORIS\\Emulation\\media\\logo.bmp"));
        }

        SECTION("Path to a BSY file.")
        {
            std::string test {
                "D:\\Studies\\Diplomamunka\\Emulated System\\Emulation\\main.bsy"
            };
            test = corrector.correct_paths(test, new_paths);
            REQUIRE_THAT(test, Equals("E:\\Diplomamunka\\BORIS\\Emulation\\main.bsy"));
        }

        SECTION("Path to a FAB file.")
        {
            std::string test {
                "D:\\Studies\\Diplomamunka\\Emulated System\\Emulation\\animation\\anim.fab"
            };
            test = corrector.correct_paths(test, new_paths);
            REQUIRE_THAT(test, Equals("E:\\Diplomamunka\\BORIS\\Emulation\\animation\\anim.fab"));
        }

        SECTION("Path to a SBL file.")
        {
            std::string test {
                "D:\\Studies\\Diplomamunka\\Emulated System\\Emulation\\lib\\engine.sbl"
            };
            test = corrector.correct_paths(test, new_paths);
            REQUIRE_THAT(test, Equals("E:\\Diplomamunka\\BORIS\\Emulation\\lib\\engine.sbl"));
        }
    }

    SECTION("Text mixed with paths")
    {
        std::string test {
            "BMPSEQ\t0\t16777215\t2\t-1\t0\t0\tCell 2: Belt\t425\t390\t375\t80\t2\t5\t"
            "D:\\Studies\\Diplomamunka\\Emulated System\\Emulation\\animation\\belt_01.bmp\t"
            "D:\\Studies\\Diplomamunka\\Emulated System\\Emulation\\animation\\belt_02.bmp\t"
            "D:\\Studies\\Diplomamunka\\Emulated System\\Emulation\\animation\\belt_03.bmp\t"
            "D:\\Studies\\Diplomamunka\\Emulated System\\Emulation\\animation\\belt_04.bmp\t"
            "D:\\Studies\\Diplomamunka\\Emulated System\\Emulation\\animation\\belt_05.bmp\t"
            "*.bmp\t*.bmp\t*.bmp\t*.bmp\t*.bmp\t0\t0\t5\t0\tC:\\Windows\\System32\\cmd.exe"
        };
        test = corrector.correct_paths(test, new_paths);

        REQUIRE_THAT(test, Equals({
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