#include <boris_corrector.h>
#include <cstdlib>
#include <iomanip>
#include <fstream>

using namespace diplomamunka;

bool diplomamunka::is_boris_file(const fs::path &p)
{
    static const std::set<std::string> supported_types{".bmp", ".bsy", ".fab", ".sbl"};

    auto extension = util::to_lower(p.extension().string());
    return supported_types.count(extension) > 0;
}

fs::path diplomamunka::add_temp_prefix(const fs::path &p)
{
    auto temp = p;
    temp.replace_filename("~$" + p.filename().string());
    return temp;
}

boris_corrector::boris_corrector(const fs::path &working_dir) : cwd(working_dir) {}

std::set<fs::path> boris_corrector::search_for_files()
{
    fs::recursive_directory_range finder(cwd);
    std::set<fs::path> files;

    std::copy_if(finder.begin(), finder.end(), std::inserter(files, files.end()), is_boris_file);
    return files;
}

std::string boris_corrector::correct_paths(const std::string &s, const std::set<fs::path> &files)
{
    static const std::regex matcher{
        R"([a-z]:\\([^\\/:*?"<>|\r\n]+\\)*[^\\/:*?"<>|\r\n]+\.(bmp|bsy|fab|sbl))",
        std::regex::ECMAScript | std::regex::icase | std::regex::nosubs | std::regex::optimize
    };
    return util::regex_replace(s, matcher, [this, &files](const std::string &match) {
        auto it = std::find_if(files.begin(), files.end(), [this, &match](const fs::path &file) {
            return fs::ends_with(match, fs::relative(file, cwd));
        });
        return it != files.end() ? it->string() : match;
    });
}

int boris_corrector::execute()
{
    const auto logPercent = [](std::size_t p) -> std::ostream & {
        return std::cout << "[" << std::setw(3) << p << "%] ";
    };

    double percentage = 0.0;
    logPercent(percentage) << "Searching for BORIS-specific files..." << std::endl;

    try
    {
        const auto files = search_for_files();
        const double step = 100.0 / static_cast<double>(files.size());
        logPercent(step / 2.0) << files.size() << " files found. " << std::endl;

        for (const auto &file : files)
        {
            logPercent(percentage += step) << "Processing file: " << file.string() << "... ";

            if (correct_file(file, files))
                std::cout << "DONE" << std::endl;
            else
                std::cout << "FAILED" << std::endl;
        }
    }
    catch (std::exception &e)
    {
        logPercent(percentage) << "Error occurred: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    logPercent(100) << "Correction finished." << std::endl;
    return EXIT_SUCCESS;
}

bool boris_corrector::correct_file(const fs::path &f, const std::set<fs::path> &files)
{
    const auto temp = add_temp_prefix(f);

    if (std::fstream in(f.string(), std::ios::in), out(temp.string(), std::ios::out); in && out)
    {
        for (std::string line; std::getline(in, line);)
            out << correct_paths(line, files) << std::endl;
    }
    else
    {
        return false;
    }

    fs::remove(f);
    fs::rename(temp, f);
    return true;
}
