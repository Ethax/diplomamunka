#pragma once

#include <iostream>
#include <set>

#include "file_system.hpp"
#include "utilities.hpp"

namespace diplomamunka
{

class boris_corrector final
{
public:
    using char_type = fs::path::value_type;
    using string_type = fs::path::string_type;

    boris_corrector(std::basic_ostream<char_type> &log_out = util::console<char_type>::out,
                    const fs::path &base = fs::current_path());

    std::set<fs::path> search_for_files();
    string_type correct_paths(const string_type &s, const std::set<fs::path> &files);
    int execute();

    static bool is_boris_file(const fs::path &p);

private:
    const fs::path cwd;
    std::basic_ostream<char_type> &logger;
};

} // namespace diplomamunka