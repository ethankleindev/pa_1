========================================================================
1. Student/Group Information
========================================================================
Group #7
Names: Ethan Klein, Gerson Mancia
Course/Section: Operating Sytems
Assignment: Programming  Assignment 1- Command Line Interpreter (MyShell)


========================================================================
2. Files Included
========================================================================
- main.cpp                : Starting point of myShell; boots up welcome message, input loop, exit detection, thread creation using
                            CreateThread(), and synchronizes with the parent using WaitForSingleObject().

- myShell.cpp             : Implements helper functions for command parsing(parseCommand), whitelist verification (isSupportedCommand),                               and the worker thread routine(commandThread)
  
- myShell.h               : Header file containing library inclusions, data structure declarations, and function prototypes

- README.txt              : Comprehensive documentation file outlining design, compilation steps, test results, and group member                                       contributions
  
- myShell.exe             : Compiled executable binary for running myShell on Windows systems.


========================================================================
3. How To Compile
========================================================================



========================================================================
4. How To Run
========================================================================


========================================================================
5. Supported Commands
========================================================================
The Following Windows operating system commands are supported:

-dir                  : Displays a list of files and subdirectories
-help                 : Provides help information for Windows commands
-vol                  : Displays disk volume label and serial number
-path                 : Displays or sets a search path for executable files
-tasklist             : Displays all currently running tasks/processes
-notepad              : Launches the Windows Notepad text editor
-echo [text]          : Displays messages or turns command echoing on/off
-color [attr]         : Sets the default console foreground and background colors
-ping [address]       : Checks ping


========================================================================
6. Threading Design
========================================================================
-Thread Spawning              : When a user enters a valid supported command, main() allocates a vector copy of the arguments on the heap
                                and calls CreateThread().
                                
-Child Execution              : CreateThread() executes command CreateThread() in a separate worker thread. This function remakes the                                     full command line and runs it using system(). It then frees the heap memory.

-Parent Synchronization       : The parent section immediately starts executing once the child is done by using the                                                       WaitForSingleObject(hThread, INFINITE) before prompting the user again. 

-Resource Cleanup             : After execution completes, the parent thread calls CloseHandle(hThread) to prevent memory leaks

-Exit/Quit Handling           : The commands "quit" or "exit" terminate the program without creating any more threads.


========================================================================
7. Testing
========================================================================



========================================================================
8. Known Limitations
========================================================================


========================================================================
9. Team Contributions
========================================================================
-Ethan Klein
-Gerson Mancia: Added comments to describe how functions worked, worked on 1 bug fix in main, created threading sections in main.cpp and also on created the helper function commandThread and helped a minor bug fix on isSupportedCommand on myShell.cpp, added the necessary libraries in myShell.h and also wrote section 1, 2, 5, 6 and 9 of this README file.
  
