// Ethan Klein
// Gerson Mancia
// Xammy Yang
// Chris Jose
// Brian Nguyen
// Programming Assignment 1

#ifndef MYSHELL_H
#define MYSHELL_H
#include <vector>
#include <string>
#include <windows.h>    //imports the windows OS datat types in order to create and manage threads

std::vector<std::string> parseCommand(const std::string&);
bool isSupportedCommand(const std::string&);
DWORD WINAPI commandThread(LPVOID lpParam); //Tells the compiler that commandThread exists and matches the signature required by CreateTheread()    

#endif
