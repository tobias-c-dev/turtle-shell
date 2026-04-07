#include "shell.hpp"
#include <iostream>

int main(){
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    run_shell();
    return 0;
}