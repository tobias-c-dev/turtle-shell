#include "parser.hpp"
#include <vector>
#include <string>
#include <cctype>

std::vector<std::string> split(const std::string& input){
    std::vector<std::string> tokens;
    std::string current;

    bool in_single = false;
    bool in_double = false;
    bool escape = false;

    for (char c : input){
        if (escape){
            current += c;
            escape = false;
            continue;
        }

        if (c == '\\'){
            // escape works outside quotes and in double quotes
            if (!in_single){
                escape = true;
                continue;
            }
        }

        if (c == '"' && !in_single){
            in_double = !in_double;
            continue;
        }

        if (c == '\'' && !in_double){
            in_single = !in_single;
            continue;
        }

        if (std::isspace(static_cast<unsigned char>(c)) && !in_single && !in_double){
            if (!current.empty()){
                tokens.push_back(current);
                current.clear();
            }
        } else {
            current += c;
        }
    }

    if (!current.empty()){
        tokens.push_back(current);
    }

    return tokens;
}