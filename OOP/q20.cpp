#include <iostream>

class Counter {
    int value_ = 0;

public:
    explicit Counter(int v = 0) : value_(v) {}

    // 1. Prefix ++: modify, then return reference to *this
    Counter& operator++() {
        ++value_;
        return *this;               // allows chaining: ++(++c)
    }

    // 2. Postfix ++: save old copy, modify *this, return the old value
    Counter operator++(int) {       // dummy int distinguishes postfix
        Counter old = *this;        // copy of the current object
        ++(*this);                  // reuse prefix ++ via *this
        return old;                 // return the saved copy
    }

    // 3. Assignment with self-assignment check
    Counter& operator=(const Counter& other) {
        if (this == &other)         // guard against c = c
            return *this;
        value_ = other.value_;
        return *this;               // enable a = b = c
    }

    // 4. Name collision: parameter vs member
    void setValue(int value) {
        this->value_ = value;       // this-> resolves ambiguity
    }

    int value() const { return value_; }
};

int q20() {
    Counter c(10);

    // Prefix
    Counter& r = ++c;
    std::cout << "after ++c: c=" << c.value() << " r=" << r.value() << "\n";
    // 11 11  — r refers to the same object as c

    // Postfix
    Counter d = c++;
    std::cout << "after c++: c=" << c.value() << " d=" << d.value() << "\n";
    // 12 11  — d holds the old value, c was incremented

    // Chaining
    Counter e;
    e = ++(++c);                    // prefix returns Counter&, so chaining works
    std::cout << "c=" << c.value() << " e=" << e.value() << "\n"; // 14 14

    // Self-assignment
    c = c;                          // guarded by this == &other
    std::cout << "after self-assign: c=" << c.value() << "\n";    // 14

    // Name collision
    Counter f;
    f.setValue(42);                 // this->value_ = value
    std::cout << "f=" << f.value() << "\n";                       // 42
}