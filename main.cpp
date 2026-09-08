// Ethan Klein
#include <iostream>
#include <string>
#include <cstring>
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
        char buffer[256];
        strncpy(buffer, input.c_str(), sizeof(buffer) - 1);
        buffer[sizeof(buffer) - 1] = '\0';
        //parse and tokenize
        std::vector <std::string> argv;
        char* token = strtok(buffer, " \0");
        while (argv.size() < 4 && token != nullptr)
        {
            argv.push_back(token);
            token = strtok(nullptr, "    ");
        }
        if (argv.empty()) continue;
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