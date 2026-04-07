#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <functional>

std::vector<std::string> split(const std::string& input) {
    std::vector<std::string> tokens;
    std::istringstream stream(input);
    std::string token;
    while (stream >> token)
        tokens.push_back(token);
    return tokens;
}

int main() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    const std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> commands = {
        {"exit", [](const std::vector<std::string>&) {
            exit(0);
        }},
        {"echo", [](const std::vector<std::string>& tokens) {
            for (size_t i = 1; i < tokens.size(); i++)
                std::cout << tokens[i] << (i + 1 < tokens.size() ? " " : "\n");
        }},
    };

    while (true) {
        std::cout << "$ ";

        std::string input;
        if (!std::getline(std::cin, input)) break;

        auto tokens = split(input);
        if (tokens.empty()) continue;

        const std::string& cmd = tokens[0];

        if (cmd == "type") {
            if (tokens.size() < 2) { std::cout << "type: missing argument\n"; continue; }
            const std::string& arg = tokens[1];
            if (commands.count(arg) || arg == "type")
                std::cout << arg << " is a shell builtin\n";
            else
                std::cout << arg << ": not found\n";
        } else if (auto it = commands.find(cmd); it != commands.end()) {
            it->second(tokens);
        } else {
            std::cout << cmd << ": command not found\n";
        }
    }
}