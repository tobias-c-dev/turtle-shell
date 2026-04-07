#include "shell.hpp"
#include "builtins.hpp"
#include "parser.hpp"
#include "executor.hpp"
#include <iostream>

void run_shell(){
    const auto commands = get_builtins();

    while (true){
        std::cout << "$ ";

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
            else {
                std::cout << arg << ": not found\n";
            }
        }
        else if (auto it = commands.find(cmd); it !=commands.end()){
            it->second(tokens);
        } else {
            std::cout << cmd << ": command not found\n";
        }
    }
}