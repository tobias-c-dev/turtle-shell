#include "builtins.hpp"
#include <iostream>

CommandMap get_builtins(){
    return {
        {"exit", [](const std::vector<std::string>&) {
            exit(0);    
        }},
        {"echo", [](const std::vector<std::string>& tokens) {
            for (size_t i=1; i < tokens.size(); i++){
                std::cout << tokens[i] << (i + 1 < tokens.size() ? " ": "\n");
            }
        }},
    };
}