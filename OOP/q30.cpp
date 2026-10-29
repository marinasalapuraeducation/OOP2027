#include <iostream>
#include <string>

// 1. Overloading by NUMBER of parameters
void print(int a) {
    std::cout << "Single int: " << a << "\n";
}

void print(int a, int b) {
    std::cout << "Two ints: " << a << " and " << b << "\n";
}

// 2. Overloading by TYPE of parameters
void print(double a) {
    std::cout << "Double: " << a << "\n";
}

void print(const std::string& s) {
    std::cout << "String: " << s << "\n";
}

// 3. Overloading by ORDER of parameters
void print(int a, double b) {
    std::cout << "Int then Double: " << a << ", " << b << "\n";
}

void print(double a, int b) {
    std::cout << "Double then Int: " << a << ", " << b << "\n";
}

int q30() {
    print(10);                  // Calls print(int)
    print(10, 20);              // Calls print(int, int)
    print(3.14);                // Calls print(double)
    print("Hello");             // Calls print(const std::string&) 
    // (Note: "Hello" is a const char*, 
    // but std::string is a better match than others)

    print(10, 3.14);            // Calls print(int, double)
    print(3.14, 10);            // Calls print(double, int)

    return 0;
}