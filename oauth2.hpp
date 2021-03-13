#pragma once

#define REQUESTS_WITH_NLOHMANN_JSON
#include "requests.hpp"

#include <vector>
#include <string>
#include <random>

struct oauth2
{
    std::string auth_endpoint;
    std::string token_endpoint;
    std::string client_id, client_secret;
    std::string redirect_uri = "";

    static std::string random_state(size_t n = 16)
    {
        std::string state(n, 'x');

        constexpr std::string_view alphabet = "abcdefghijklmnopqrstuvwxyz"
                                              "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                              "0123456789";
        static std::mt19937 gen(std::random_device{}());
        static std::uniform_int_distribution<> dist(0, alphabet.size() - 1);

        for (auto &c : state) { c = alphabet[dist(gen)]; }

        return state;
    }

    struct authorization_url_res_t
    {
        requests::url url;
        std::string state;
    };

    enum class response_type {code, token};

    auto authorization_url(
        response_type rt,
        std::vector<std::string_view> scopes,
        const std::string &state = random_state()
    ) const
    {
        authorization_url_res_t res { { auth_endpoint }, state };

        std::string scope;
        for (const auto &s : scopes)
        {
            if (!scope.empty()) { scope += "%20"; }
            scope += s;
        }

        std::string response = rt == response_type::code ? "code" : "token";

        requests::query q = {{
            { "response_type", response },
            { "client_id", client_id },
            { "scope", scope },
            { "state", state },
            { "redirect_uri", redirect_uri }
        }};

        res.url.query = requests::urlencoded(q);

        return res;
    }


    auto authorization_url(
        std::vector<std::string_view> scopes,
        const std::string &state = random_state()
    ) const { return authorization_url(response_type::code, scopes, state); }

    struct token
    {
        std::string access_token;
        std::string token_type;
        unsigned expires_in = 0;
        std::string refresh_token = ""; // Possibly empty
        std::string scope;
    };

    token access_token(const std::string &code)
    {
        auto r = requests::post(
            { token_endpoint },
            requests::data{{
                { "grant_type", "authorization_code" },
                { "code", code },
                { "client_id", client_id },
                { "client_secret", client_secret },
                { "redirect_uri", redirect_uri }
            }}
        );
        auto json = r.json();
        return token{
            json["access_token"].get<std::string>(),
            json["token_type"].get<std::string>(),
            json["expires_in"].get<unsigned>(),
            json["refresh_token"].get<std::string>(),
            json["scope"].get<std::string>()
        };
    }
};