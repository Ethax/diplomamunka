#pragma once

#include <iostream>
#include <set>

#include "file_system.hpp"
#include "utilities.hpp"

namespace diplomamunka
{

bool is_boris_file(const fs::path &p);

class boris_corrector final
{
  public:
    boris_corrector(const fs::path &working_dir = fs::current_path());

    std::set<fs::path> search_for_files();
    std::string correct_paths(const std::string &s, const std::set<fs::path> &files);
    int execute();

  private:
    const fs::path cwd;
};

} // namespace diplomamunka