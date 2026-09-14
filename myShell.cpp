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
    char* token = strtok(buffer, " \t\r\n");                //<--  this is because fgets(); takes the \n line as literal parts of the word 
    while (argumentVector.size() < 4 && token != nullptr)  // as in if we pass an argument "dir" fgets(); will read it as "dir\n" literally
    {                                                      //in the buffer. We want to make sure that strtok will remove \r and \n. \r
        argumentVector.push_back(token);                  // makes it so the cursor moves to the beginning of a line, and \n moves it down
        token = strtok(nullptr, " \t");                  // a row. 
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
