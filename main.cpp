// Ethan Klein
// Gerson Mancia
// Xammy Yang
// Chris Jose
// Brian Nguyen
// Programming Assignment 1

#include "myShell.h"
#include <iostream>
#include <string>
#include <vector>

int main()
{
   
    std::cout << "Welcome to myShell\n"; //welcome message

    // Keep reading commands until exit, quit, or the end of input.
    while(1)
    {
        //read input
        std::string input;
        std::cout << "\n==> ";
        std::getline(std::cin, input);
        // Stop if there is no more input.
        if (!std::cin) break;

        // Reject long lines so the parser does not cut off the command.
        if (input.size() >= 256)
        {
            std::cout << "Use at most 255 characters.\n";
            continue;
        }

        //parse input into vector of tokens
        std::vector<std::string> argv = parseCommand(input);
        if (argv.empty()) continue;

        if (argv[0] == "exit" || argv[0] == "quit") break; //exit check

        // Allow the command plus up to three arguments.
        if (argv.size() > 4)
        {
            std::cout << "Use at most 4 tokens (command plus 3 arguments).\n";
            continue;
        }

        //check command against whitelist
        if (!isSupportedCommand(argv[0]))
        {
            std::cout << "Command not supported: " << argv[0] << "\n";
            continue;
        }
        // Block symbols that could run extra commands.
        if (input.find_first_of("&|<>^%!\"") != std::string::npos)
        {
            std::cout << "Shell operators and quoted arguments are not supported.\n";
            continue;
        }

       // The worker gets its own copy and deletes it when done.
       //allocates memory for args to pass to child thread
       auto threadArgs = new std::vector<std::string>(argv);

       //Spawn child worker thread
       HANDLE hThread = CreateThread(NULL, 0, commandThread, threadArgs, 0, NULL);

       if(hThread == NULL)
       {
          std::cout << "Error creating child thread.\n";
          delete threadArgs;                                    //prevents memory leaks
          continue;                                             //skips this section to continue loop again
       }

       // Wait here before asking for the next command.
       //Wait for child thread execution to finish
       WaitForSingleObject(hThread, INFINITE);

       //Close thread handle
       CloseHandle(hThread);
    }

    std::cout << "Thanks for using myShell!\n"; //exit message
    return 0;
}
