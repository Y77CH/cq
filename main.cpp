#include <iostream>
#include "oauth2.hpp"

int main()
{
    oauth2 oauth {
        .auth_endpoint = "https://discord.com/api/oauth2/authorize",
        .token_endpoint = "https://discord.com/api/oauth2/token",
        .client_id = "795251827507068998",
        .client_secret = "RQ4u0I1fjA1qkENcWhbzcnsJMqxO5TsA"
    };
    std::cout << oauth.authorization_url({"identify", "email"}).url.to_string() << "\n";

    std::string url_str;
    std::cin >> url_str;
    auto res = requests::urldecoded(requests::url(url_str).query);

    auto token = oauth.access_token(res["code"]);
    std::cout << token.access_token << "\n";
    std::cout << token.expires_in << "\n";
    std::cout << token.refresh_token << "\n";
    std::cout << token.scope << "\n";
    std::cout << token.token_type << "\n";
    return 0;
}