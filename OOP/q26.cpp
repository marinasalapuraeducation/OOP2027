//26. What are the differences between a constructor and a destructor?
#include <iostream>
#include <string>
#include <utility>

class Widget {
private:
    std::string name_;
    int* data_;

public:
    // --- CONSTRUCTORS ---

    // 1. Default constructor
    Widget() : name_("unnamed"), data_(new int[10]) {
        std::cout << "ctor(): " << name_ << "\n";
    }

    // 2. Parameterized constructor
    explicit Widget(std::string name) : name_(std::move(name)), data_(new int[10]) {
        std::cout << "ctor(string): " << name_ << "\n";
    }

    // --- DESTRUCTOR ---

    // 3. Destructor (no params, no return type, no overloading)
    virtual ~Widget() {
        delete[] data_;     // release resource acquired in constructor
        std::cout << "dtor: " << name_ << "\n";
    }

    // 4. For demonstration: throw in constructor (allowed)
    static Widget createRisky() {
        throw std::runtime_error("failed to create");
    }
};

// --- Inheritance and virtual destructors ---
class Base {
public:
    Base() { std::cout << "  Base()\n"; }
    virtual ~Base() { std::cout << "  ~Base()\n"; } // MUST be virtual
};

class Derived : public Base {
    Widget w_{ "derived-member" }; // member with its own ctor/dtor
public:
    // Inherit Base's constructors (ctors can be inherited)
    using Base::Base;

    // Derived constructor
    Derived() { std::cout << "  Derived()\n"; }

    // Destructor (cannot inherit, but automatically calls base dtor)
    ~Derived() override { std::cout << "  ~Derived()\n"; }
};

int q26() {
    std::cout << "--- 1. Overloading constructors ---\n";
    {
        Widget w1;                 // calls Widget()
        Widget w2("Alpha");        // calls Widget(string)
    } // dtors run in reverse order (w2 then w1)

    std::cout << "\n--- 2. Constructor vs Destructor execution order ---\n";
    {
        Derived d;
        // Output order:
        //   Base()      <- base constructed first
        //   ctor(string): derived-member <- member constructed next
        //   Derived()   <- derived body runs last
        //   ~Derived()  <- derived body runs first on destruction
        //   dtor: derived-member <- members destroyed next
        //   ~Base()     <- base destroyed last
    }

    std::cout << "\n--- 3. Exception in constructor ---\n";
    try {
        Widget::createRisky();     // throws before object is fully created
    }
    catch (const std::exception& e) {
        std::cout << "Caught: " << e.what() << " (no destructor called for the object)\n";
    }
}