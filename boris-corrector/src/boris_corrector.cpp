#include <boris_corrector.h>

using namespace diplomamunka;
using namespace diplomamunka::literals;

bool diplomamunka::is_boris_file(const fs::path &p)
{
    static const std::set<fs::path> supported_types { ".bmp", ".bsy", ".fab", ".sbl" };

    auto extension = util::to_lower(p.extension().native());
    return supported_types.count(extension);
}

boris_corrector::boris_corrector(const fs::path &base, std::basic_ostream<char_type> &log_out)
    : cwd(base), logger(log_out) {}

std::set<fs::path> boris_corrector::search_for_files()
{
    fs::recursive_directory_range finder(cwd);
    std::set<fs::path> files;

    std::copy_if(finder.begin(), finder.end(), std::inserter(files, files.end()), is_boris_file);
    return files;
}

boris_corrector::string_type
boris_corrector::correct_paths(const string_type &s, const std::set<fs::path> &files)
{
    static const std::basic_regex<char_type> matcher {
        "[a-z]:\\\\([^\\\\/:*?\"<>|\\r\\n]+\\\\)*[^\\\\/:*?\"<>|\\r\\n]+\\.(bmp|bsy|fab|sbl)"_bs,
        std::regex::ECMAScript | std::regex::icase | std::regex::nosubs | std::regex::optimize
    };

    return util::regex_replace(s, matcher, [this, &files](const string_type &match) {
        auto it = std::find_if(files.begin(), files.end(), [this, &match](const fs::path &file) {
            return fs::ends_with(match, fs::relative(file, cwd));
        });
        return it != files.end() ? it->native() : match;
    });
}

int boris_corrector::execute()
{
    return 0;
}
