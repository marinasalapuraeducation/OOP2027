#include <iostream>
#include <array>
#include <vector>
#include <memory>
#include <string>
#include <utility>

class Widget {
    std::string name_;
    int         id_;
public:
    // default ctor — required by fixed-size arrays and vector(n)
    Widget() : name_("unnamed"), id_(0) {
        std::cout << "  default ctor: " << name_ << "\n";
    }
    // parameterized ctor
    Widget(std::string name, int id) : name_(std::move(name)), id_(id) {
        std::cout << "  ctor: " << name_ << " #" << id_ << "\n";
    }
    // copy ctor
    Widget(const Widget& o) : name_(o.name_), id_(o.id_) {
        std::cout << "  copy ctor: " << name_ << "\n";
    }
    ~Widget() {
        std::cout << "  dtor: " << name_ << "\n";
    }

    void dump() const {
        std::cout << "    [" << id_ << "] " << name_ << "\n";
    }
};

int q21() {
    std::cout << "=== 1. C-style array (stack, fixed size) ===\n";
    {
        Widget arr[3];                       // default-constructs 3 elements
        arr[0] = Widget("A", 1);             // assignment (copy/move)
        arr[1] = Widget("B", 2);
        for (const auto& w : arr) w.dump();
    }   // destructors run in reverse order

    std::cout << "\n=== 2. std::array (stack, fixed size, safe) ===\n";
    {
        std::array<Widget, 3> arr;           // default-constructs 3 elements
        arr[0] = Widget("C", 3);
        arr[1] = Widget("D", 4);
        for (const auto& w : arr) w.dump();
    }

    std::cout << "\n=== 3. std::vector with default ctor (dynamic size) ===\n";
    {
        std::vector<Widget> v(3);            // 3 default-constructed elements
        v[0] = Widget("E", 5);
        for (const auto& w : v) w.dump();
    }

    std::cout << "\n=== 4. std::vector + emplace_back (no default ctor needed) ===\n";
    {
        std::vector<Widget> v;
        v.reserve(3);                        // avoid reallocations
        v.emplace_back("F", 6);              // constructed in place with args
        v.emplace_back("G", 7);
        v.emplace_back("H", 8);
        for (const auto& w : v) w.dump();
    }

    std::cout << "\n=== 5. std::vector with initializer list ===\n";
    {
        std::vector<Widget> v = {
            Widget("I", 9),
            Widget("J", 10),
            Widget("K", 11),
        };
        for (const auto& w : v) w.dump();
    }

    std::cout << "\n=== 6. new[] / delete[] (legacy, avoid) ===\n";
    {
        Widget* arr = new Widget[3];         // default-constructs 3 elements
        arr[0] = Widget("L", 12);
        for (int i = 0; i < 3; ++i) arr[i].dump();
        delete[] arr;                        // must match new[]
    }

    std::cout << "\n=== 7. unique_ptr<T[]> (RAII over new[]) ===\n";
    {
        auto arr = std::make_unique<Widget[]>(3);   // 3 default-constructed
        arr[0] = Widget("M", 13);
        for (int i = 0; i < 3; ++i) arr[i].dump();
    }   // automatically delete[]'d

    std::cout << "\n=== 8. vector of unique_ptr (polymorphic array) ===\n";
    {
        std::vector<std::unique_ptr<Widget>> v;
        v.push_back(std::make_unique<Widget>("N", 14));
        v.push_back(std::make_unique<Widget>("O", 15));
        for (const auto& p : v) p->dump();
    }

    std::cout << "\n=== done ===\n";
}