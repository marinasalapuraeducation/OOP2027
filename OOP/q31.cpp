#include <iostream>
#include <string>

// --- 1. Define the overloads ---
void print(int x) { std::cout << "print(int)\n"; }
void print(double x) { std::cout << "print(double)\n"; }
void print(const char* s) { std::cout << "print(const char*)\n"; }
void print(bool b) { std::cout << "print(bool)\n"; }

// An ambiguous overload set
void process(int a, double b) { std::cout << "process(int, double)\n"; }
void process(double a, int b) { std::cout << "process(double, int)\n"; }

int main() {
    // --- Exact Matches ---
    print(42);            // Exact match: print(int)
    print(3.14);          // Exact match: print(double)
    print("Hello");       // Exact match: print(const char*)
    print(true);          // Exact match: print(bool)

    // --- Promotions ---
    char c = 'A';
    print(c);             // char promotes to int -> print(int)
    float f = 2.5f;
    print(f);             // float promotes to double -> print(double)

    // --- Standard Conversions ---
    short s = 10;
    print(s);             // short promotes to int -> print(int)

    // --- Ambiguity ---
    // process(10, 20.0); 
    // ERROR: Ambiguous. 
    // Option A: process(int, double) requires 1 exact match, 1 exact match.
    // Option B: process(double, int) requires 2 conversions.
    // Wait, actually Option A is better! Let's look at a true ambiguity:

    // Ambiguous:
    process(10.0f, 20.0f);
    // ERROR: Both arguments are float.
    // Option A: process(int, double) -> requires standard conversion (float->int) and promotion (float->double)
    // Option B: process(double, int) -> requires promotion (float->double) and standard conversion (float->int)
    // The compiler ranks them equally, resulting in an ambiguity error.

    return 0;
}