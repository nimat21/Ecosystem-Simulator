#include "Helper.h"

void Helper::moveCursor(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H"; // ANSI escape code to move cursor to (x, y)
}

void Helper::clearScreen() {
    std::cout << "\033[2J\033[1;1H"; // ANSI escape code to clear the screen
}

void Helper::sleep(int s) {
    std::this_thread::sleep_for(std::chrono::milliseconds(s));
}

bool Helper::fileExists(const std::filesystem::path& fullFilePath) {
    return std::filesystem::exists(fullFilePath) && std::filesystem::is_regular_file(fullFilePath);
}

std::filesystem::path Helper::getValidTextFile(const std::string& promptMessage, const std::filesystem::path& inputFolderPath) {
    std::string userFileName;
    bool validPath = false;

    while (!validPath) {
        std::cout << promptMessage;
        std::getline(std::cin, userFileName); // Read the entire line, including spaces

        if (userFileName == "quit") {
            quit(0);
        }

        // Check if the input contains any whitespace characters
        if (userFileName.find_first_of(" \t") != std::string::npos) {
            std::cout << "Error: File name should not contain spaces. Please enter a valid file name." << std::endl;
            continue;
        }

        std::filesystem::path fullFilePath = inputFolderPath;
        if (!inputFolderPath.empty()) {
            fullFilePath /= userFileName;
        } else {
            fullFilePath = userFileName;
        }

        // Check if the input already ends with ".txt"
        if (userFileName.size() >= 4 && userFileName.substr(userFileName.size() - 4) == ".txt") {
            if (fileExists(fullFilePath)) {
                validPath = true;
                return fullFilePath;
            } else {
                std::cout << "File does not exist or is not a text file. Please enter a valid file name." << std::endl;
            }
        } else {
            fullFilePath += ".txt";
            if (fileExists(fullFilePath)) {
                validPath = true;
                return fullFilePath;
            } else {
                std::cout << "File does not exist or is not a text file. Please enter a valid file name." << std::endl;
            }
        }
    }

    // This line will never be reached, but included to avoid compiler warnings/errors
    return "";
}

int Helper::getUserChoice(int min_choice, int max_choice){
    int choice;
    bool validInput = false;

    while (!validInput) {
        if (!(std::cin >> choice) || choice < min_choice || choice > max_choice) {
            std::cout << "Invalid input. Please select a valid choice between " << min_choice << " and " << max_choice << '\n';
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            validInput = true;
        }
    }
    return choice;
}

int Helper::getPositiveInteger(const std::string& prompt){
    int user_int;
    bool validInput = false;

    while (!validInput) {
        std::cout << prompt;
        if (!(std::cin >> user_int) || user_int <= 0) {
            std::cout << "Invalid input. Please enter a positive integer.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            validInput = true;
        }
    }
    return user_int;
}

void Helper::quit(int error_code){
    if (error_code == 0)
        std::cout << "Thank you for using this program!\n";
    exit(error_code);
}