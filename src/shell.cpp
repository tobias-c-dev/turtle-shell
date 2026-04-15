#include "shell.hpp"
#include "builtins.hpp"
#include "parser.hpp"
#include "executor.hpp"
#include <iostream>
#include <filesystem>

void run_shell(){
    const auto commands = get_builtins();
    const std::string FONTGREEN = "\033[1;32m";
    const std::string FONTCYAN  = "\033[1;36m";
    const std::string FONTYELLOW = "\033[1;33m";
    const std::string FONTMAGENTA = "\033[1;35m";
    const std::string FONTRESET = "\033[0m";

    while (true){

        const char* user = getenv("USER");
        std::string path = std::filesystem::current_path().string();
        const char* home = getenv("HOME");

        if (home) {
            std::string homeStr = home;
            if (path.rfind(homeStr, 0) == 0){
                path = "~" + path.substr(homeStr.length());
            }
        }



        std::cout << FONTMAGENTA
          << (user ? user : "unknown") 
          << ":" 
          << path
          << "$ "
          << FONTYELLOW;

        std::string input;
        if (!std::getline(std::cin, input)) break;

        auto tokens = split(input);
        if (tokens.empty()) continue;

        const std::string& cmd = tokens[0];

        if (cmd == "type"){
            if (tokens.size() < 2) {std::cout << "type: missing argument\n"; continue;}
            const std::string& arg = tokens[1];
            if (commands.count(arg) || arg == "type"){
                std::cout << arg << " is a shell builtin\n";
            }
            else if (exists_in_path(arg)){
                std::cout << arg << ": is in Path\n";
            }
            else {
                std::cout << arg << ": not found\n";
            }
        }
        else if (auto it = commands.find(cmd); it !=commands.end()){
            it->second(tokens);
        } else {
            execute(tokens);
        }
    }
}