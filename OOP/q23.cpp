#include <iostream>
#include <string>

class Widget {
public:
    int    id = 0;                       // public data member
    std::string name = "unnamed";           // public data member

    void show() const {                     // public member function
        std::cout << "Widget #" << id << ": " << name << "\n";
    }
};

int q23() {
    Widget w;                    // object on the stack

    // --- dot operator: access through an OBJECT ---
    w.id = 42;                 // set public data member
    w.name = "Gadget";           // set public data member
    w.show();                    // call public member function

    std::cout << w.id << " " << w.name << "\n";

    // --- arrow operator: access through a POINTER ---
    Widget* p = &w;
    p->id = 7;                   // equivalent to (*p).id = 7
    p->show();

    // --- dot operator on a reference ---
    Widget& r = w;
    r.name = "Ref";              // dot works on references too
    r.show();
}