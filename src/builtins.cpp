#include "builtins.hpp"
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <sstream>
#include <filesystem>

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
        {"cd", [](const std::vector<std::string>& tokens) {
            auto remove_quotes= [](const std::string& s) {
                std::string result;
                for (char c : s) {
                    if (c != '"' && c != '\'') {
                        result += c;
                    }
                }
                return result;
            };

            if (tokens.size() == 1  ){
                const char* home = getenv("HOME");
                if (home) chdir(home);
                return;
            }

            std::string path = remove_quotes(tokens[1]);

            if (!path.empty() && path[0] == '~') {
                const char* home = getenv("HOME");
                if (home) {
                    path = std::string(home) + path.substr(1);
                }
            }

            if (chdir(path.c_str()) != 0){
                std::cerr << "cd: " << path << ": No such file or directory\n";
            }
        }},
    };
}

bool exists_in_path(const std::string& cmd) {
    const char* path_env = getenv("PATH");
    if (!path_env) return false;

    std::stringstream ss(path_env);
    std::string dir;
    
    while (std::getline(ss, dir, ':')) {
        std::filesystem::path full = dir + "/" + cmd;
        if (std::filesystem::exists(full)) return true;
    }
    return false;
}