# Car Service Management System

## Description

A modular C++ application using OOP principles to manage a car service. The system handles customer information, vehicle details, service appointments, mechanics, and service history, with data persistence using text files and a console-based user interface with a specific color theme (e.g., blue and white, using windows.h).

## Features

-   Manage customers and their vehicles
-   Manage service appointments (appointments are saved to data.txt)
-   List mechanics
-   Track service history
-   Data persistence via .txt files
-   Console UI with blue & white color theme

## Directory Structure

```
include/
  models/         # Data entity headers (Customer, Vehicle, etc.)
  ui/             # UI class headers (MainMenu, CustomerMenu)
  data/           # Data persistence headers (DataStorage)
  Utilities.h     # Helper functions
src/
  models/         # Data entity implementations
  ui/             # UI class implementations
  data/           # Data persistence implementations
  Utilities.cpp   # Helper function implementations
main.cpp          # Application entry point
LICENSE           # MIT License 2025
README.md         # Project description
```

## Compilation & Execution

Use a Windows environment with g++:

```
g++ src/models/*.cpp src/ui/*.cpp src/data/*.cpp src/Utilities.cpp main.cpp -o car_service.exe -I include -lws2_32 && car_service.exe
```

## Notes

-   Requires Windows for console color (windows.h)
-   Data is stored in plain text files (define file formats in DataStorage)
-   Extend stub functions for full functionality
-   UI uses a blue & white color theme for consistency
-   "Add service record" is now labeled as "Log completed service" in the UI
