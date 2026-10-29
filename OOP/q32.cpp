#include <iostream>
#include <string>
#include <utility>

class Student {
private:
    std::string name_;
    int         age_;
    double      gpa_;

public:
    // 1. Default constructor (no arguments)
    Student() : name_("Unknown"), age_(0), gpa_(0.0) {
        std::cout << "ctor(): Default\n";
    }

    // 2. Constructor with one parameter
    explicit Student(std::string name)
        : name_(std::move(name)), age_(0), gpa_(0.0) {
        std::cout << "ctor(string): " << name_ << "\n";
    }

    // 3. Constructor with two parameters
    Student(std::string name, int age)
        : name_(std::move(name)), age_(age), gpa_(0.0) {
        std::cout << "ctor(string, int): " << name_ << ", " << age_ << "\n";
    }

    // 4. Constructor with three parameters
    Student(std::string name, int age, double gpa)
        : name_(std::move(name)), age_(age), gpa_(gpa) {
        std::cout << "ctor(string, int, double): " << name_ << ", " << age_ << ", " << gpa_ << "\n";
    }

    // 5. Delegating constructor (calls the 3-parameter constructor)
    Student(int age) : Student("Anonymous", age, 0.0) {
        std::cout << "  (delegated from ctor(int))\n";
    }

    void print() const {
        std::cout << "  -> " << name_ << ", " << age_ << ", GPA: " << gpa_ << "\n";
    }
};

int q32() {
    Student s1;                                  // Calls ctor()
    Student s2("Alice");                         // Calls ctor(string)
    Student s3("Bob", 20);                       // Calls ctor(string, int)
    Student s4("Charlie", 22, 3.8);              // Calls ctor(string, int, double)
    Student s5(19);                              // Calls ctor(int) -> delegates to ctor(string, int, double)

    std::cout << "\n--- Objects created ---\n";
    s1.print();
    s2.print();
    s3.print();
    s4.print();
    s5.print();

    return 0;
}