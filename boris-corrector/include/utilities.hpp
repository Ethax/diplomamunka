#include <string>
#include <regex>
#include <iostream>
#include <locale>

namespace util
{

template <typename T>
struct console;

template <>
struct console<char>
{
    static constexpr std::basic_ostream<char> &out = std::cout;
    static constexpr std::basic_ostream<char> &err = std::cerr;
    static constexpr std::basic_ostream<char> &log = std::clog;
};

template <>
struct console<wchar_t>
{
    static constexpr std::basic_ostream<wchar_t> &out = std::wcout;
    static constexpr std::basic_ostream<wchar_t> &err = std::wcerr;
    static constexpr std::basic_ostream<wchar_t> &log = std::wclog;
};

template <typename T>
class iterator_range
{
public:
    iterator_range(const T &first, const T &last) : first_(first), last_(last) {}

    T begin() { return first_; }
    T end() { return last_; }

private:
    T first_, last_;
};

template <typename Traits, typename CharT, typename UnaryOperation>
auto regex_replace(const std::basic_string<CharT> &s,
                   const std::basic_regex<CharT, Traits> &rx,
                   UnaryOperation replace)
{
    using string_type = std::basic_string<CharT>;
    using iterator_type = std::regex_iterator<typename string_type::const_iterator>;

    auto tail = s.begin();
    string_type result;

    for (const auto &match : iterator_range<iterator_type>({s.begin(), s.end(), rx}, {}))
    {
        result.append(match.prefix().first, match.prefix().second);
        result.append(replace(match.str()));
        tail = match.suffix().first;
    }

    result.append(tail, s.end());
    return result;
}

template <typename InputIt, typename CharT>
auto join(InputIt first, InputIt last, const std::basic_string<CharT> &separator)
{
    using string_type = std::basic_string<CharT>;

    string_type result;
    if (first != last)
    {
        result.append(*first);
        ++first;
    }
    for (auto &&elem : iterator_range<InputIt>(first, last))
    {
        result.append(separator).append(elem);
    }
    return result;
}

template <typename InputIt, typename CharT>
auto join(InputIt first, InputIt last, const CharT *separator)
{
    return join(first, last, std::basic_string<CharT>(separator));
}

template <typename CharT>
auto to_lower(const std::basic_string<CharT> &s)
{
    std::basic_string<CharT> result;
    std::transform(s.begin(), s.end(), std::back_inserter(result), [](CharT ch) {
        return std::tolower(ch, std::locale());
    });
    return result;
}

template <typename CharT>
auto to_upper(const std::basic_string<CharT> &s)
{
    std::basic_string<CharT> result;
    std::transform(s.begin(), s.end(), std::back_inserter(result), [](CharT ch) {
        return std::toupper(ch, std::locale());
    });
    return result;
}

} // namespace util