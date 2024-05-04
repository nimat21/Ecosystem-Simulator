#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <cctype>
#include <algorithm>
#include <filesystem>

/*
Helper class with various useful methods that can be used anywhere
*/
class Helper {
public:
    /*
    Move cursor to specified x/y location on terminal
    */
    static void moveCursor(int x, int y);

    /*
    Clear terminal
    */
    static void clearScreen();

    /*
    Sleep for s milliseconds
    */
    static void sleep(int s);

    /*
    Check if this file path exists
    */
    static bool fileExists(const std::filesystem::path& fullFilePath);

    /*
    Continually ask user to enter a valid file name. End the loop only if
    1. user enters valid file name
    2. user enters "quit"
    */
    static std::filesystem::path getValidTextFile(const std::string& promptMessage, const std::filesystem::path& inputFolderPath = "");

    /*
    Get a valid integer choice from the user.
    This is good for when the user has to select a numerical choice from a menu.
    */
    static int getUserChoice(int min_choice, int max_choice);

    /*
    Get a valid positive integer from the user (greater than 0)
    */
    static int getPositiveInteger(const std::string& prompt);

    /*
    Quit the program.
    Error codes:
    0 - successful termination (nothing went wrong)
    1 - Bad file path given for map
    2 - Valid file path given for map, but couldn't read file
    3 - Bad file path given for species list
    4 - Valid file path given for species list, but couldn't read file
    5 - Invalid species given in map
    6 - Inavlid arguments given in species list
    7 - Health not given as integer
    8 - Error with command line arguments
    9 - Tried to move an animal in a way that is not allowed
    */
    static void quit(int error_code);
};

#endif