#include <boris_corrector.h>

using namespace diplomamunka;

bool diplomamunka::is_boris_file(const fs::path &p)
{
    static const std::set<std::string> supported_types { ".bmp", ".bsy", ".fab", ".sbl" };

    auto extension = util::to_lower(p.extension().string());
    return supported_types.count(extension) > 0;
}

boris_corrector::boris_corrector(const fs::path &working_dir): cwd(working_dir) {}

std::set<fs::path> boris_corrector::search_for_files()
{
    fs::recursive_directory_range finder(cwd);
    std::set<fs::path> files;

    std::copy_if(finder.begin(), finder.end(), std::inserter(files, files.end()), is_boris_file);
    return files;
}

std::string boris_corrector::correct_paths(const std::string &s, const std::set<fs::path> &files)
{
    static const std::regex matcher {
        "[a-z]:\\\\([^\\\\/:*?\"<>|\\r\\n]+\\\\)*[^\\\\/:*?\"<>|\\r\\n]+\\.(bmp|bsy|fab|sbl)",
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
    return 0;
}
