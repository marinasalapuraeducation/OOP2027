#include <iostream>

class Math {
public:
    // 1. Defined INSIDE the class declaration
    //    Implicitly marked as 'inline' by the compiler
    int add(int a, int b) {
        return a + b;
    }

    // 2. Declared inside, defined OUTSIDE
    //    NOT implicitly inline (unless you explicitly write 'inline')
    int multiply(int a, int b);
};

// Definition outside the class
int Math::multiply(int a, int b) {
    return a * b;
}

int q27() {
    Math m;
    std::cout << m.add(2, 3) << "\n";      // Inlined (likely)
    std::cout << m.multiply(2, 3) << "\n"; // Not inline (unless compiler optimizes)
}