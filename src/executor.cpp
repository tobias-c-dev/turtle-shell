#include "executor.hpp"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

void execute(const std::vector<std::string>& tokens){
    std::vector<char*> args;
    for (const auto& t : tokens)
        args.push_back(const_cast<char*>(t.c_str()));
    args.push_back(nullptr);

    pid_t pid = fork();

    if (pid == 0){
        execvp(args[0], args.data());
        std::cerr << tokens[0] << ": command not found\n";
        exit(1);
    }
    else if (pid > 0){
        waitpid(pid, nullptr, 0);
    }
    else{
        std::cerr << "fork failed\n";
    }
}