#include <boris_corrector.h>

using namespace diplomamunka;

namespace
{

using namespace std::regex_constants;
constexpr syntax_option_type options = ECMAScript | icase | nosubs | optimize;

template <typename CharT>
struct path_validator;

template <>
struct path_validator<char>
{
    static constexpr char pattern[]{""};
};

template <>
struct path_validator<wchar_t>
{
    static constexpr wchar_t pattern[]{L""};
};

} // namespace

boris_corrector::boris_corrector(std::basic_ostream<char_type> &log_out, const fs::path &base)
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
    static const std::basic_regex<char_type> rx(path_validator<char_type>::pattern, options);
    return {};
}

int boris_corrector::execute()
{
    return 0;
}

bool boris_corrector::is_boris_file(const fs::path &p)
{
    static const std::set<fs::path> supported_types{".bmp", ".bsy", ".fab", ".sbl"};

    auto extension = util::to_lower(p.extension().native());
    return supported_types.count(extension);
}