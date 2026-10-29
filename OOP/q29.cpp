class MyClass; // Forward declaration (no body, no members)

#pragma once
#include <vector>

// Forward declaration: we only store pointers to Child
class Child;

class Parent {
private:
    std::vector<Child*> children_; // Pointer is OK with incomplete type
public:
    Parent() = default;
    ~Parent(); // Destructor declared, defined in .cpp

    void addChild(Child* c);
    void printChildren() const;
};
#include "Parent.h"
#include "Child.h" // Now we NEED the full definition of Child
#include <iostream>

// Destructor must be defined in the .cpp file where Child is a complete type!
Parent::~Parent() = default;

void Parent::addChild(Child* c) {
    children_.push_back(c);
    c->setParent(this);
}

void Parent::printChildren() const {
    for (const auto* c : children_) {
        std::cout << c->getName() << "\n"; // Requires complete type
    }
}

#include "Parent.h"
#include "Child.h"
#include <iostream>

int q29() {
    Parent p;
    Child c1("Alice");
    Child c2("Bob");

    p.addChild(&c1);
    p.addChild(&c2);
    p.printChildren();
}