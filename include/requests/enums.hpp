#ifndef REQUESTS_ENUMS_HPP
#define REQUESTS_ENUMS_HPP


#include <array>
#include <concepts>
#include <limits>
#include <optional>
#include <stdexcept>
#include <string_view>
#include <type_traits>


// Helpers for LibRequests enums
namespace requests::enums {

/**
 * @brief:
 *  Enums' values must be in [min, max] range.
 *  User must change it if any value is not in a default range.
 *
 * @note Default range - [0, 127]
 *
 * @tparam E Enum type
 */
template<typename E> requires std::is_enum_v<E>
struct enum_range
{
    using U = std::underlying_type_t<E>;

    static constexpr auto min = std::max(static_cast<U>(0),   std::numeric_limits<U>::min());
    static constexpr auto max = std::min(static_cast<U>(127), std::numeric_limits<U>::max());
};



// Case sensitive comparator for enum names
using case_sensitive = std::equal_to<std::string_view>;

// Case insensitive comparator for enum names
struct case_insensitive
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



// Not a part of API
namespace detail {

// Use compiler hacks to get enum entry name
template <typename E, E V>
consteval auto name() noexcept
{
    // Name of the function cutted to the end of enum entry's name
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
        !(name.front() >= '0' && name.front() <= '9')
    ) { return name; }

    // Return blank on invalid
    return std::string_view{};
}


template<typename E, size_t ...Is>
consteval auto range([[maybe_unused]] std::index_sequence<Is...> _)
{
    constexpr auto min = enum_range<E>::min;

    return std::array<bool, sizeof...(Is)>{
        {(name<E, static_cast<E>(Is + min)>() != "")...}
    };
}

/**
 * @brief:
 *  Get bool[range_size] array where every i element
 *  says whether enum E contains value == i + enum_range<E>::min.
 */
template<typename E>
consteval auto range()
{
    constexpr auto min = enum_range<E>::min;
    constexpr auto max = enum_range<E>::max;
    constexpr auto range_size = max - min + 1;

    return range<E>(std::make_index_sequence<range_size>());
}

} // namespace detail



// Get number of values in enum
template<typename E> requires std::is_enum_v<E>
consteval size_t enum_size()
{
    constexpr auto r = detail::range<E>();

    size_t n = 0;
    for (size_t i = 0; i < r.size(); ++i) { if (r[i]) { ++n; } }

    return n;
}



// Get array of all enum values (within enum range)
template<typename E> requires std::is_enum_v<E>
consteval auto enum_values()
{
    constexpr auto r = detail::range<E>();
    constexpr auto s = enum_size<E>();

    // Fill in valid enum values
    std::array<E, s> values {};
    for (std::size_t i = 0, v = 0; v < s; ++i)
    {
        if (r[i]) { values[v++] = static_cast<E>(i + enum_range<E>::min); }
    }

    return values;
}



// Add names helper to detail
namespace detail {

// Get array of enum names (within enum range)
template<typename E, size_t ...Is>
consteval auto names([[maybe_unused]] std::index_sequence<Is...> _)
{
    return std::array<std::string_view, sizeof...(Is)>{
        {name<E, enum_values<E>()[Is]>()...}
    };
}

} // namespace detail

// Get array of all enum names (within enum range)
template<typename E> requires std::is_enum_v<E>
consteval auto enum_names()
{
    constexpr auto s = enum_size<E>();
    return detail::names<E>(
        std::make_index_sequence<s>{}
    );
}


// Get position of enum value (if there is) inside of enum values array
template<typename E> requires std::is_enum_v<E>
constexpr std::optional<size_t> enum_index(E v) noexcept
{
    constexpr auto vs = enum_values<E>();

    for (size_t i = 0; i < vs.size(); ++i)
    {
        if (vs[i] == v) { return i; }
    }

    return {};
}

// Get position of enum name (if there is) inside of enum names array
template<typename E, typename NameEqual = case_sensitive>
    requires std::is_enum_v<E> &&
    requires(NameEqual eq) {
        { eq("", "") } -> std::same_as<bool>;
    }
constexpr std::optional<size_t> enum_index(
    std::string_view n, const NameEqual &eq = NameEqual()
) noexcept
{
    constexpr auto ns = enum_names<E>();

    for (size_t i = 0; i < ns.size(); ++i)
    {
        if (eq(ns[i], n)) { return i; }
    }

    return {};
}


// Get enum value by its name (if there is)
template<typename E, typename NameEqual = case_sensitive>
    requires std::is_enum_v<E> &&
    requires(NameEqual eq) {
        { eq("", "") } -> std::same_as<bool>;
    }
constexpr std::optional<E> enum_value(
    std::string_view n, const NameEqual &eq = NameEqual()
) noexcept
{
    auto i = enum_index<E>(n, eq);

    if (!i.has_value()) { return {}; }

    return enum_values<E>()[i.value()];
}


// Get enum value's name (empty if not found)
template<typename E> requires std::is_enum_v<E>
constexpr std::string_view enum_name(E v) noexcept
{
    auto i = enum_index<E>(v);

    if (!i.has_value()) { return {}; }

    return enum_names<E>()[i.value()];
}



/**
 * @brief Maps enum entries with their names
 *
 * @note Enum values must be within enum range
 */
template<typename E, typename NameEqual = case_sensitive>
    requires std::is_enum_v<E> &&
    requires(NameEqual eq) {
        { eq("", "") } -> std::same_as<bool>;
    }
class enum_wrapper
{
public:
    // Default constructor
    constexpr enum_wrapper() noexcept = default;

    // Wrapp enum entry
    constexpr enum_wrapper(
        E e, [[maybe_unused]] const NameEqual &eq = NameEqual()) noexcept : m_e(e)
    {}

    // Create and wrapp enum entry by its entry name
    constexpr enum_wrapper(
        std::string_view n, const NameEqual &eq = NameEqual())
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


    // Explicitly get enum entry
    [[nodiscard]] E& as_enum() noexcept { return m_e; }

    // Explicitly get enum entry
    [[nodiscard]] constexpr E as_enum() const noexcept { return m_e; }

    // Get enum entry's name
    [[nodiscard]] constexpr std::string_view as_view() const
    {
        auto n = enum_name<E>(m_e);

        if (n == "")
        {
            throw std::logic_error(
                "Can't find name for enum value == " +
                std::to_string(static_cast<std::underlying_type_t<E>>(m_e)) +
                ". Change enum_range!"
            );
        }

        return n;
    }


    // Implicitly get enum entry
    operator E&() noexcept { return m_e; }

    // Implicitly get enum entry
    constexpr operator E() const noexcept { return m_e; }


private:
    E m_e;
};

} // namespace requests::enums

#endif // REQUESTS_ENUMS_HPP