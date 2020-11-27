#include "requests/options/auth.hpp"

#include <bitset>


std::string encode_base64(std::string_view str) noexcept
{
    constexpr std::string_view base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                              "abcdefghijklmnopqrstuvwxyz"
                                                            "0123456789+/";

    std::string res; res.reserve(str.size() * 1.33);

    while (str.size() >= 3)
    {
        std::string bits; bits.reserve(24);
        for (size_t i = 0; i < 3; ++i)
        {
            bits += std::bitset<8>{static_cast<unsigned long long>(str[i])}.to_string();
        }

        for (size_t i = 0; i < 4; ++i)
        {
            res += base64_chars[std::bitset<6>(bits, i*6).to_ulong()];
        }

        str.remove_prefix(3);
    }

    if (str.size() == 2)
    {
        std::string bits; bits.reserve(18);
        for (size_t i = 0; i < 2; ++i)
        {
            bits += std::bitset<8>{static_cast<unsigned long long>(str[i])}.to_string();
        }
        bits += "00";

        for (size_t i = 0; i < 3; ++i)
        {
            res += base64_chars[std::bitset<6>(bits, i*6).to_ulong()];
        }
        res += "=";
    }
    else if (str.size() == 1)
    {
        std::string bits {std::bitset<8>{static_cast<unsigned long long>(str[0])}.to_string() + "0000"};

        for (size_t i = 0; i < 2; ++i)
        {
            res += base64_chars[std::bitset<6>(bits, i*6).to_ulong()];
        }
        res += "==";
    }

    return res;
}


std::string Requests::Auth::to_base64() const noexcept
{
    return encode_base64(username + ":" + password);
}