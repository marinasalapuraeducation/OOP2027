#include <iostream>
#include <string>

// ---- Class: the blueprint ----
class Counter {
private:
    int value_ = 0;              // per-object state (each object gets its own)
    static int created_;         // shared by ALL objects (belongs to the class)

public:
    Counter() { ++created_; }   // each construction increments the shared counter
    ~Counter() { --created_; }

    void increment() { ++value_; }
    int  value() const { return value_; }

    static int created() { return created_; }  // class-level query
};

int Counter::created_ = 0;       // definition of the static member

int q6() {
    // One class, many independent objects:
    Counter a;                   // object #1
    Counter b;                   // object #2

    a.increment();
    a.increment();
    b.increment();

    std::cout << "a.value = " << a.value() << "\n";   // 2
    std::cout << "b.value = " << b.value() << "\n";   // 1  (independent state)
    std::cout << "created = " << Counter::created() << "\n"; // 2 (shared)

    {
        Counter c;               // a third object with its own lifetime
        c.increment();
        std::cout << "c.value = " << c.value() << "\n"; // 1
        std::cout << "created = " << Counter::created() << "\n"; // 3
    }                            // c destroyed here

    std::cout << "created = " << Counter::created() << "\n"; // 2
}