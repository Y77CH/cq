#include "requests/url.hpp"

#include <regex>
#include <stdexcept>


requests::url::url(std::string_view url)
{
    // BNF for http/https (from RFC1738):
    //
    //  ; URL schemeparts for ip based protocols:
    //
    //  hostport       = host [ ":" port ]
    //  host           = hostname | hostnumber
    //  hostname       = *[ domainlabel "." ] toplabel
    //  domainlabel    = alphadigit | alphadigit *[ alphadigit | "-" ] alphadigit
    //  toplabel       = alpha | alpha *[ alphadigit | "-" ] alphadigit
    //  alphadigit     = alpha | digit
    //  hostnumber     = digits "." digits "." digits "." digits
    //  port           = digits
    //
    //  ; HTTP
    //
    //  httpurl  = "http://" hostport [ "/" hpath [ "?" search ]]
    //  hpath    = hsegment *[ "/" hsegment ]
    //  hsegment = *[ uchar | ";" | ":" | "@" | "&" | "=" ]
    //  search   = *[ uchar | ";" | ":" | "@" | "&" | "=" ]
    //
    //  ; Miscellaneous definitions
    //
    //  lowalpha = "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" |
    //             "i" | "j" | "k" | "l" | "m" | "n" | "o" | "p" |
    //             "q" | "r" | "s" | "t" | "u" | "v" | "w" | "x" |
    //             "y" | "z"
    //  hialpha  = "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" |
    //             "J" | "K" | "L" | "M" | "N" | "O" | "P" | "Q" | "R" |
    //             "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z"
    //
    //  alpha       = lowalpha | hialpha
    //  digit       = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
    //  safe        = "$" | "-" | "_" | "." | "+"
    //  extra       = "!" | "*" | "'" | "(" | ")" | ","
    //  national    = "{" | "}" | "|" | "\" | "^" | "~" | "[" | "]" | "`"
    //  punctuation = "<" | ">" | "#" | "%" | <">
    //
    //  reserved    = ";" | "/" | "?" | ":" | "@" | "&" | "="
    //  hex         = digit | "A" | "B" | "C" | "D" | "E" | "F" |
    //                        "a" | "b" | "c" | "d" | "e" | "f"
    //  escape      = "%" hex hex
    //
    //  unreserved  = alpha | digit | safe | extra
    //  uchar       = unreserved | escape
    //  xchar       = unreserved | reserved | escape
    //  digits      = 1*digit

    // Starts with http(s) followed by :// in any case
    std::regex rscheme("^(https?)://", std::regex_constants::icase);

    // Find scheme
    std::cmatch match;
    if (!std::regex_search(url.data(), match, rscheme))
    {
        throw std::logic_error("Not a valid URL!");
    }
    // Get scheme without ://
    std::string scheme_str = match.str(1);
    // Convert scheme to lowercase
    std::transform(
        scheme_str.begin(), scheme_str.end(),
        scheme_str.begin(), [](auto &&c){ return std::tolower(c); }
    );
    // Get enum scheme
    scheme = scheme_t{scheme_str};
    // Remove found
    url.remove_prefix(match.str().size());


    /* Regex helpers */
    const std::string hostnumber  {"(([0-9]{1,3}\\.){3}[0-9]{1,3})"};
    const std::string toplabel    {"([a-z][-a-z0-9]*[a-z0-9])"};
    const std::string domainlabel {"([a-z0-9][-a-z0-9]*[a-z0-9])"};
    const std::string hostname    {"((" + domainlabel + "\\.)*" + toplabel + ")"};

    // Starts with valid host
    std::regex rhost(
        "^(" + hostname + "|" + hostnumber + ")",
        std::regex_constants::icase | std::regex_constants::nosubs
    );

    // Find host
    if (!std::regex_search(url.data(), match, rhost))
    {
        throw std::logic_error("Not a valid URL!");
    }
    // Get host
    host = match.str();
    // Convert host to lowercase
    std::transform(
        host.begin(), host.end(),
        host.begin(), [](auto &&c){ return std::tolower(c); }
    );
    // Remove found
    url.remove_prefix(match.str().size());


    // Starts with optional port
    std::regex rport("^(:([0-9]{1,5}))?");

    // Find port
    std::regex_search(url.data(), match, rport);
    if (match.str().empty())
    {
        // Change port to default if not specified
        port = static_cast<uint16_t>(scheme);
    }
    else
    {
        // Get specified port
        port = std::stoul(match.str(2));
    }
    // Remove found
    url.remove_prefix(match.str().size());


    /* Regex helpers */
    const std::string escape   {"(%[0-9a-f]{2})"};
    const std::string hsegment {"(([-$_.+;:@&=!*'(),a-z0-9]|" + escape + ")*)"};

    // Starts with optional path
    std::regex rpath(
        "^(/" + hsegment + ")*",
        std::regex_constants::icase | std::regex_constants::nosubs
    );

    // Find path
    std::regex_search(url.data(), match, rpath);
    // Get specified path or ""
    path = match.str();
    // Change path if empty
    if (path.empty()) { path = "/"; }
    // Remove found
    url.remove_prefix(match.str().size());


    // Starts with optional query
    std::regex rquery("^(?:\\?" + hsegment + ")?", std::regex_constants::icase);

    // Find query
    std::regex_search(url.data(), match, rquery);
    // Get specified query or ""
    query = match.str(1);
    // Remove found
    url.remove_prefix(match.str().size());



    // BNF for fragments can be found in RFC3986:
    // Note: syntax a little bit different from the one used in RFC1738

    // Starts with optional query
    std::regex rfragment("^(?:#" + hsegment + ")?", std::regex_constants::icase);

    // Find query
    std::regex_search(url.data(), match, rfragment);
    // Get specified query or ""
    fragment = match.str(1);
    // Remove found
    url.remove_prefix(match.str().size());
}

std::string requests::url::as_string() const noexcept
{
    std::string res;

    res += scheme.as_view();

    res += "://";

    res += host;

    res += ":" + std::to_string(port);

    res += path;

    if (!query.empty())    { res += "?" + query; }

    if (!fragment.empty()) { res += "#" + fragment; }

    return res;
}