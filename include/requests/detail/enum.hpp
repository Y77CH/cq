#ifndef REQUESTS_DETAIL_ENUM_HPP
#define REQUESTS_DETAIL_ENUM_HPP

#include <array>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>


namespace Requests::Detail {

// Enum values must be in this range.
template<typename E>
struct Enum_Range
{
    static constexpr auto min = 0;
    static constexpr auto max = 255;
};



// Comparators for enum names
inline namespace Comparators {

// Default comparator for enum names
using Case_Sensitive = std::equal_to<std::string_view>;

// Comparator for enum names
struct Case_Insensitive
{
    constexpr bool operator()(std::string_view lhs, std::string_view rhs) const noexcept
    {
        if (lhs.size() != rhs.size()) { return false; }

        for (size_t i = 0; i < lhs.size(); ++i)
        {
            auto c1 = ('A' <= lhs[i] && lhs[i] <= 'Z') ? (lhs[i] - 'A' + 'a') : lhs[i];
            auto c2 = ('A' <= rhs[i] && rhs[i] <= 'Z') ? (rhs[i] - 'A' + 'a') : rhs[i];
            if (c1 != c2) { return false; }
        }

        return true;
    }
};

} // namespace Comparators



// Use compiler hacks to get enum name
template<typename E, E V>
consteval auto name() noexcept
{
    // Name of the function cutted to the end of enum value's name
    std::string_view name {__PRETTY_FUNCTION__, sizeof(__PRETTY_FUNCTION__) - 2};

    // Find where enum value name ends from the end
    for (std::size_t i = name.size(); i > 0; --i)
    {
        // One of the ending symbols
        if (
            name[i - 1] == ' ' ||
            name[i - 1] == ')' ||
            name[i - 1] == ':'
        )
        {
            // Leave only possible name
            name.remove_prefix(i);
            break;
        }
    }

    // Return name if valid
    if (
        !(name.empty()) &&
        !(name.front() == '-') &&
        !(name.front() >= '0'  && name.front() <= '9')
    ) { return name; }

    // Return blank on invalid
    return std::string_view{};
}


// Helper function for range()
template<typename E, size_t ...Is>
consteval auto range(std::index_sequence<Is...>)
{
    constexpr auto min = Enum_Range<E>::min;

    return std::array<bool, sizeof...(Is)>{
        { (name<E, static_cast<E>(Is + min)>() != "")... }
    };
}

/**
 * @brief:
 *  Get bool[range_size] array where every i element
 *  is true if enum contains value == i + Enum_Range<E>::min.
 */
template<typename E>
consteval auto range()
{
    constexpr auto min = Enum_Range<E>::min;
    constexpr auto max = Enum_Range<E>::max;
    constexpr auto range_size = max - min + 1;

    return range<E>(std::make_index_sequence<range_size>{});
}


// Get number of values in enum
template<typename E>
consteval size_t enum_size()
{
    constexpr auto r = range<E>();

    size_t n = 0;
    for (size_t i = 0; i < r.size(); ++i) { if (r[i]) { ++n; } }

    return n;
}


// Get array of enum values
template<typename E>
consteval auto enum_values()
{
    constexpr auto s = enum_size<E>();
    constexpr auto r = range<E>();

    // Fill in valid enum values
    std::array<E, s> values {};
    for (std::size_t i = 0, v = 0; v < s; ++i)
    {
        if (r[i]) { values[v++] = static_cast<E>(i + Enum_Range<E>::min); }
    }

    return values;
}


// Helper for enum_names()
template<typename E, size_t ...Is>
consteval auto enum_names(std::index_sequence<Is...>)
{
    return std::array<std::string_view, sizeof...(Is)>{
        { name<E, enum_values<E>()[Is]>()... }
    };
}

// Get array of enum names
template<typename E>
consteval auto enum_names()
{
    constexpr auto s = enum_size<E>();
    return enum_names<E>(std::make_index_sequence<s>{});
}


// Get position inside of enum values array
template<typename E>
constexpr std::optional<size_t> enum_index(E v) noexcept
{
    constexpr auto vs = enum_values<E>();

    for (size_t i = 0; i < vs.size(); ++i)
    {
        if (vs[i] == v) { return i; }
    }

    return {};
}


// Get position inside of enum names array
template<typename E, typename NameEqual = Case_Sensitive>
constexpr std::optional<size_t> enum_index(
    std::string_view n, const NameEqual &eq = {}
) noexcept
{
    constexpr auto ns = enum_names<E>();

    for (size_t i = 0; i < ns.size(); ++i)
    {
        if (eq(ns[i], n)) { return i; }
    }

    return {};
}


// Get enum value by its name
template<typename E, typename NameEqual = Case_Sensitive>
constexpr std::optional<E> enum_value(
    std::string_view n, const NameEqual &eq = {}
) noexcept
{
    auto i = enum_index<E>(n, eq);

    if (!i.has_value()) { return {}; }

    return enum_values<E>()[i.value()];
}


// Get enum value's name (empty if not found)
template<typename E>
constexpr std::string_view enum_name(E v) noexcept
{
    auto i = enum_index<E>(v);

    if (!i.has_value()) { return {}; }

    return enum_names<E>()[i.value()];
}



// Enum Wrapper
template<typename E, typename NameEqual = Case_Sensitive>
class Enum
{
public:
    constexpr Enum() noexcept = default;

    // Wrapp enum value
    constexpr Enum(E e, const NameEqual & = {}) noexcept : m_e(e) {}

    // Wrapp enum by its name
    constexpr Enum(std::string_view n, const NameEqual &eq = {})
    {
        auto v = enum_value<E>(n, eq);

        if (!v.has_value())
        {
            throw std::invalid_argument(
                "Can't find value with name " + std::string{n}
            );
        }

        m_e = v.value();
    }

    // Wrapp enum by its name
    Enum(const char *n, const NameEqual &eq = {}) : Enum(std::string_view{n}, eq) {}


    [[nodiscard]] constexpr E to_enum() const noexcept { return m_e; }

    // Convert to enum value's name
    [[nodiscard]] constexpr std::string_view to_view() const noexcept
    {
        return enum_name<E>(m_e);
    }

    // Convert to enum value's name
    [[nodiscard]] std::string to_string() const noexcept
    {
        return std::string{enum_name<E>(m_e)};
    }


    operator E&() noexcept { return m_e; }

    constexpr operator E() const noexcept { return m_e; }

private:
    E m_e;
};

} // namespace Requests::Detail

#endif // REQUESTS_DETAIL_ENUM_HPP