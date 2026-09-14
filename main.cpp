// Ethan Klein
//Gerson Mancia

#include "myShell.h"
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

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

        if (argv[0] == "exit" || argv[0] == "quit") break; //exit check

        //check command against whitelist
        if (!isSupportedCommand(argv[0]))
        {
            std::cout << "Command not supported\n" << argv[0] << "\n";
            continue;
        }
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

       //Wait for child thread execution to finish
       WaitForSingleObject(hThread, INFINITE);

       //Close thread handle
       CloseHandle(hThread);
    }

    std::cout << "Thanks for using myShell!\n"; //exit message
    return 0;
}
