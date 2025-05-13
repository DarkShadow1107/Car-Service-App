#ifndef UTILITIES_H
#define UTILITIES_H
#include <string>
#include <windows.h>
#include <iostream>
namespace Utilities {
    // Theme color mapping:
    // #690B22 (dark red)   -> 4
    // #E07A5F (salmon)     -> 12
    // #F1E3D3 (cream)      -> 15
    // #1B4D3E (dark green) -> 2
    // #474E93 (blue)       -> 1
    // #7E5CAD (purple)     -> 5
    // #72BAA9 (teal)       -> 3
    // #D5E7B5 (lt green)   -> 10
    enum ThemeColor {
        THEME_DARK_RED = 4,
        THEME_SALMON = 12,
        THEME_CREAM = 15,
        THEME_DARK_GREEN = 2,
        THEME_BLUE = 1,
        THEME_PURPLE = 5,
        THEME_TEAL = 3,
        THEME_LT_GREEN = 10
    };
    void setConsoleColor(int color);
    bool isValidPhoneNumber(const std::string& phone);
    int getIntInput(const std::string& prompt);
    std::string getStringInput(const std::string& prompt);
}

#endif // UTILITIES_H