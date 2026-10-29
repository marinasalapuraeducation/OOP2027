#include <iostream>
#include <string>

// ---------- class: members private by default ----------
class Account {
    std::string owner_;      // private by default (before any specifier)
    double      balance_;    // still private
public:
    Account(std::string owner, double b)
        : owner_(std::move(owner)), balance_(b) {
    }

    double balance() const { return balance_; }   // public accessor
    const std::string& owner() const { return owner_; }
};

// ---------- struct: members public by default ----------
struct Point {
    int x;                   // public by default
    int y;                   // public by default
};

// ---------- mixed: specifiers change the default mid-body ----------
class Mixed {
    int a_;                  // private (class default)
public:
    int b_;                  // public
private:
    int c_;                  // private again
protected:
    int d_;                  // protected
public:
    int e_;                  // public
};

// ---------- default inheritance differs ----------
class Base {
public:
    void hello() const { std::cout << "Base::hello\n"; }
};

struct PubDerived : Base {};     // public inheritance
class  PrivDerived : Base {};    // private inheritance (class default!)

int main() {
    // --- class: private default blocks access ---
    Account acc("Alice", 100.0);
    std::cout << acc.owner() << ": " << acc.balance() << "\n";  // OK
    // acc.balance_ = 999;       // ERROR: private by default
    // acc.owner_ = "Bob";       // ERROR: private by default

    // --- struct: public default allows access ---
    Point p{ 1, 2 };
    p.x = 10;                    // OK: public
    p.y = 20;                    // OK
    std::cout << p.x << "," << p.y << "\n";

    // --- default inheritance ---
    PubDerived pd;
    pd.hello();                  // OK: public inheritance (struct default)

    PrivDerived pv;
    // pv.hello();               // ERROR: Base::hello is private in PrivDerived
}