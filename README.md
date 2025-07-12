# ANSI Terminal-Based Spreadsheet Program

This repository contains two versions of a terminal-based spreadsheet program, developed for the **CSE241 - Object Oriented Programming** course at Gebze Technical University.

Both versions simulate basic spreadsheet functionalities in a text-based terminal interface using ANSI escape sequences.


 Project Structure

- `SpreadSheet Program` → Initial version
- `Spreadsheet Program Enhanced` → Extended version with modern C++ features


 Version 1: Basic Spreadsheet (C++)

This version implements a simplified spreadsheet that supports:

- ANSI terminal grid rendering
- Cell-based navigation
- Basic text input
- Class-based modular design

Technologies

- Language: C++
- Features used: Classes, basic OOP, I/O streams


Version 2: Enhanced Spreadsheet (Modern C++)

This version extends the initial project with advanced C++ features and modern programming practices.

 Key Enhancements:

- Dynamic memory management  
- Use of smart pointers (`std::shared_ptr`, `std::unique_ptr`)  
- Exception handling  
- Namespaces for modularity  
- Templated classes  
- Deepened class hierarchy and design

Technologies

- Language: Modern C++ (C++11 and above)
- Features used: OOP + Templates + RAII + Exceptions


How to Compile

For both versions, compile with g++ (or any C++11+ compatible compiler):

```bash
g++ -std=c++11 -o spreadsheet main.cpp
./spreadsheet
