#include <iostream>
#include <stdexcept>
//1. Encapsulation
class BankAccount {
private:
    double balance_;                 // hidden internal state

public:
    explicit BankAccount(double initial) : balance_(initial) {
        if (initial < 0) throw std::invalid_argument("negative balance");
    }

    void deposit(double amount) {    // controlled access
        if (amount <= 0) throw std::invalid_argument("bad amount");
        balance_ += amount;
    }

    double balance() const { return balance_; }  // read-only accessor
};

int q21() {
    BankAccount acc(100.0);
    acc.deposit(50.0);
    // acc.balance_ = -999;          // ERROR: private
    std::cout << acc.balance() << "\n";  // 150
}

//2. Inheritance

#include <iostream>
#include <string>

class Animal {
public:
    explicit Animal(std::string name) : name_(std::move(name)) {}
    virtual ~Animal() = default;

    virtual void speak() const { std::cout << name_ << " makes a sound\n"; }

protected:
    std::string name_;
};

class Dog : public Animal {          // Dog IS-A Animal
public:
    using Animal::Animal;            // inherit constructor
    void speak() const override {    // override base behavior
        std::cout << name_ << " says Woof\n";
    }
};

int q22() {
    Dog d("Rex");
    d.speak();                       // Rex says Woof
}

//3. Polymorphism

#include <iostream>
#include <memory>
#include <vector>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;   // pure virtual -> abstract class
};

class Circle : public Shape {
    double r_;
public:
    explicit Circle(double r) : r_(r) {}
    double area() const override { return 3.14159 * r_ * r_; }
};

class Square : public Shape {
    double s_;
public:
    explicit Square(double s) : s_(s) {}
    double area() const override { return s_ * s_; }
};

int q23() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(2.0));
    shapes.push_back(std::make_unique<Square>(3.0));

    for (const auto& s : shapes)
        std::cout << s->area() << "\n";   // calls the correct override at runtime
}

//4. Abstraction

#include <iostream>

// Abstract interface: the caller only knows "what", not "how"
class Logger {
public:
    virtual ~Logger() = default;
    virtual void log(const std::string& msg) = 0;
};

// A concrete implementation hidden behind the interface
class ConsoleLogger : public Logger {
public:
    void log(const std::string& msg) override {
        std::cout << "[LOG] " << msg << "\n";
    }
};

void doWork(Logger & logger) {        // depends only on the abstraction
    logger.log("work started");
}

int q24() {
    ConsoleLogger cl;
    doWork(cl);                      // [LOG] work started
}

