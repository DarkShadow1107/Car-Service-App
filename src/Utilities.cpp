#include "../include/Utilities.h"
#include <iostream>
#include <windows.h>
#include <limits>

using namespace std;

namespace Utilities {
void setConsoleColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
bool isValidPhoneNumber(const std::string& phone) {
    for (char c : phone) if (!isdigit(c) && c != '+') return false;
    return !phone.empty();
}
int getIntInput(const std::string& prompt) {
    int value;
    std::cout << prompt;
    std::cin >> value;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}
std::string getStringInput(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}
}