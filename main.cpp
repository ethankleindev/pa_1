// Ethan Klein
#include "myShell.h"
#include <iostream>
#include <string>
#include <vector>

int main()
{
   
    std::cout << "Welcome to myShell\n"; //welcome message

    while(1)
    {
        //read input
        std::string input;
        std::cout << "\n==> ";
        std::getline(std::cin, input);

        //parse input into vector of tokens
        std::vector<std::string> argv = parseCommand(input);
        if (argv.empty()) continue;
        
        //check command against whitelist
        if (!isSupportedCommand(argv[0]))
        {
            std::cout << "Command not supported\n";
        }

        // testing, prints argv vector
        size_t i = 0;
        while (i < argv.size())
        {
            std::cout << argv[i] << " ";
            ++i;
        }
        std::cout << std::endl;

        if (argv[0] == "exit" || argv[0] == "quit") break;
    }

    std::cout << "myShell has exited\n"; //exit message
    return 0;
}