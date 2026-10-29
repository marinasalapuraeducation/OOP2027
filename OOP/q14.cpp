#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Widget {
    std::string name_;
public:
    // default constructor
    Widget() : name_("default") {
        std::cout << "ctor(): " << name_ << "\n";
    }
    // parameterized constructor
    explicit Widget(std::string n) : name_(std::move(n)) {
        std::cout << "ctor(string): " << name_ << "\n";
    }
    // copy constructor
    Widget(const Widget& o) : name_(o.name_) {
        std::cout << "copy ctor: " << name_ << "\n";
    }
    // move constructor
    Widget(Widget&& o) noexcept : name_(std::move(o.name_)) {
        std::cout << "move ctor: " << name_ << "\n";
    }
    ~Widget() {
        std::cout << "dtor: " << name_ << "\n";
    }
};

int q14() {
    std::cout << "--- 1. automatic object (stack) ---\n";
    {
        Widget a;                    // ctor() called
        Widget b("stack");           // ctor(string) called
    }                                // dtors called automatically at scope exit

    std::cout << "--- 2. dynamic object (heap) ---\n";
    {
        auto p = new Widget("heap"); // ctor(string) called by new
        delete p;                    // dtor called automatically by delete
    }

    std::cout << "--- 3. temporary ---\n";
    Widget("temp");                  // ctor(string) + dtor for the temporary

    std::cout << "--- 4. inside a container ---\n";
    {
        std::vector<Widget> v;
        v.emplace_back("in-vector"); // ctor(string) called in place
    }                                // dtor called automatically when vector dies

    std::cout << "--- 5. smart pointer ---\n";
    {
        auto sp = std::make_unique<Widget>("smart"); // ctor(string) called
    }                                // dtor called automatically by unique_ptr

    std::cout << "--- end of main ---\n";
}