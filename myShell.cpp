// Ethan Klein
//Gerson Mancia
// Programming Assignment 1

#include "myShell.h"
#include <cstring>
#include <cstdlib>


std::vector<std::string> parseCommand(const std::string& input)
{
    char buffer[256];
    strncpy(buffer, input.c_str(), sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    
    // Split the input into words using spaces and line endings.
    //parse and tokenize
    std::vector <std::string> argumentVector;
    char* token = strtok(buffer, " \t\r\n");                //<--  this is because fgets(); takes the \n line as literal parts of the word 
    while (argumentVector.size() < 4 && token != nullptr)  // as in if we pass an argument "dir" fgets(); will read it as "dir\n" literally
    {                                                      //in the buffer. We want to make sure that strtok will remove \r and \n. \r
        argumentVector.push_back(token);                  // makes it so the cursor moves to the beginning of a line, and \n moves it down
        token = strtok(nullptr, " \t\r\n");              // a row. In certain OS's it will send "dir\r\n" and this will make it filter it out 
    }
    // Keep a fifth word so main can reject too many arguments.
    if (token != nullptr) argumentVector.push_back(token);
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

DWORD WINAPI commandThread(LPVOID lpParam)
{
    // Get the command words that main passed to this worker.
    auto args = static_cast<std::vector<std::string>*>(lpParam);    //copies all the information from lpParam's address and stores each word into a vector, it does this with a pointer to access each individual cell
    if (args != nullptr && !args->empty())
    {
        // Put the words back together with spaces between them.
        std::string fullCommand = "";
        for (size_t i = 0; i < args-> size(); ++i)      // gets each individual word in the lpParam and copies them to store the command
            {
                fullCommand += (*args)[i];
                if(i < args-> size() - 1)
                {
                    fullCommand += " ";
                }
            }                               
        system(fullCommand.c_str());       //Runs it on the child thread while main.cpp waits
    }
    delete args;              //Prevents data leaks
    return 0;
}

