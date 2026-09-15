========================================================================
1. Student/Group Information
========================================================================
Group #7
Names: Ethan Klein, Gerson Mancia, Xammy Yang, Brain Nguyen, Chris Jose
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
Compiler: MinGW-w64 GCC (g++), C++17, x64, on Windows 11.
Toolchain used: w64devkit, which bundles g++ and the Windows headers and
requires no installer or administrator rights.

Steps:
  1. Download w64devkit from https://github.com/skeeto/w64devkit/releases
     and extract it to C:\w64devkit
  2. Run C:\w64devkit\w64devkit.exe to open its shell.
  3. Change into the project folder, for example:
       cd C:/pa1/pa_1-main
  4. Build:
       g++ -std=c++17 -Wall -Wextra -o myShell.exe main.cpp myShell.cpp

The build completes with no errors and no warnings, and produces myShell.exe
in the same folder.
========================================================================
4. How To Run
========================================================================
From a Windows command prompt, in the folder containing myShell.exe:
    myShell.exe
The shell prints "Welcome to myShell", then displays the "==> " prompt and waits for input. Type a supported command and press Enter. Type exit to terminate.
 
myShell.exe can also be launched by double clicking it in File Explorer, but running it from an existing command prompt is recommended so the window stays open after the shell exits.

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
All tests were run on Windows 11 using myShell.exe built with g++.
 
Test 1: dir
Typed dir with no arguments. It printed the directory listing for
C:\pa1\pa_1-main, then the prompt came back.
See Screenshot 1.
 
Test 2: ping 192.168.1.1
Typed ping with one argument. It printed the four ping attempts and the
statistics at the end. All four timed out because that address is not on our
network, which is normal ping behavior and not a problem with the shell. The
prompt did not come back until ping was finished, so the parent really is
waiting on the child thread.
See Screenshot 2.
 
Test 3: echo Hello World
Typed a command with two arguments. It printed Hello World. The parser split
this into echo, Hello, and World, which is 3 tokens and under our 4 token
limit.
See Screenshot 3.
 
Test 4: invalidCommand
Typed a command that is not on the whitelist. The shell printed
"Command not supported: invalidCommand" and went back to the prompt. It did
not create a thread and it did not crash.
See Screenshot 4.
 
Test 5: vol then path
Ran two valid commands back to back. vol printed the volume name and serial
number, then path printed the PATH variable. The shell kept working fine after
the first thread finished.
See Screenshot 5.
 
Test 6: color 0A
The console turned green on black and printed nothing, which is what color
does when it works.
See Screenshot 6.
 
Test 7: exit
The shell printed "Thanks for using myShell!" and closed. No thread is created
for exit because the exit check happens before the whitelist check.
See Screenshot 7.
 
We also tested quit and it did the same thing as exit.
 
One other thing we noticed: typing "color OA" with a letter O instead of a
zero made Windows print the color help text instead of changing the color.
Our shell passed the argument through and kept running, which is expected
since we only check the command name and not the arguments.


========================================================================
8. Known Limitations
========================================================================


========================================================================
9. Team Contributions
========================================================================
-Ethan Klein
-Gerson Mancia: Added comments to describe how functions worked(the ones on the side), worked on 1 bug fix in main, created threading sections in main.cpp and also created the helper function commandThread and helped a minor bug fix on isSupportedCommand on myShell.cpp, added the necessary libraries in myShell.h and also wrote section 1, 2, 5, 6 and 9 of this README file.
-Chris Jose: Set up the g++ build environment and confirmed the program
compiles with no errors or warnings. Ran all of the required test cases (no
arguments, one argument, multiple arguments, invalid command, two commands in
a row, color, and exit/quit), took and labeled Screenshots 1 through 7, and
wrote sections 3, 4, and 7 of this README.
  
