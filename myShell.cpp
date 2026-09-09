// Ethan Klein
#include "myShell.h"
#include <cstring>


std::vector<std::string> parseCommand(const std::string& input)
{
    char buffer[256];
    strncpy(buffer, input.c_str(), sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    
    //parse and tokenize
    std::vector <std::string> argumentVector;
    char* token = strtok(buffer, " \t");
    while (argumentVector.size() < 4 && token != nullptr)
    {
        argumentVector.push_back(token);
        token = strtok(nullptr, " \t");
    }
    return argumentVector;
}

bool isSupportedCommand(const std::string& command)
{
    //whitelisting
    static const std::vector<std::string> whiteList = {"dir", "help", "vol", "path", "tasklist", "notepad", "echo", "color", "ping"};
    for (const auto& elem : whiteList)
    {
        if (elem == command)
        {
            return true;
        }
    }
    return false;   
}