#pragma once

#include <experimental/filesystem>
#include <algorithm>
#include <iterator>

namespace fs
{

using namespace std::experimental::filesystem;

inline path::iterator operator+(path::iterator it, path::iterator::difference_type n)
{
    return std::next(it, n);
}

inline path subpath(path::iterator first, path::iterator last)
{
    path result = *first++;
    while (first != last)
        result /= *first++;
    return result;
}

inline path relative(const path &p, const path &base = current_path())
{
    const auto [p_it, base_it] = std::mismatch(p.begin(), p.end(), base.begin(), base.end());
    return (base_it == base.end()) ? subpath(p_it, p.end()) : path();
}

inline bool ends_with(const path &p, const path &suffix)
{
    const auto p_len = std::distance(p.begin(), p.end());
    const auto suffix_len = std::distance(suffix.begin(), suffix.end());

    return p_len >= suffix_len &&
           std::equal(p.begin() + (p_len - suffix_len), p.end(), suffix.begin(), suffix.end());
}

class recursive_directory_range
{
public:
    recursive_directory_range(path p) : p_(p) {}
    auto begin() { return recursive_directory_iterator(p_); }
    auto end() { return recursive_directory_iterator(); }

private:
    path p_;
};

} // namespace fs