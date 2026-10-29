#include <iostream>
#include <string>

// ---------------------------------------------------------------
// Case 1: NO constructor declared → compiler creates a trivial one
// ---------------------------------------------------------------
struct A {
    int x;
    double y;
};
// Compiler declares A::A() — trivial, does nothing.
// After `A a;` → a.x, a.y are INDETERMINATE.

// ---------------------------------------------------------------
// Case 2: ANY constructor declared → implicit default is suppressed
// ---------------------------------------------------------------
class B {
public:
    explicit B(int v) : v_(v) {}   // user-declared ctor
private:
    int v_;
};
// B b;      // ERROR: no default constructor
// B b(5);   // OK

// ---------------------------------------------------------------
// Case 3: explicitly ask for the default ctor back
// ---------------------------------------------------------------
class C {
public:
    C() = default;                 // request compiler-generated default
    explicit C(int v) : v_(v) {}
private:
    int v_ = 0;                    // in-class initializer → safe default
};

// ---------------------------------------------------------------
// Case 4: implicit default ctor is DELETED (const member, no init)
// ---------------------------------------------------------------
class D {
    const int id_;                 // const without initializer
public:
    explicit D(int id) : id_(id) {}
    // implicit D() is deleted → D d; is a compile error
};

// ---------------------------------------------------------------
// Case 5: implicit default ctor is DELETED (member has no default ctor)
// ---------------------------------------------------------------
class Member {
public:
    explicit Member(int v) : v_(v) {}
    int v_;
};
class E {
    Member m_;                     // Member has no default ctor
public:
    E() : m_(0) {}                 // must initialize m_ explicitly
    // without this line, implicit E() would be deleted
};

// ---------------------------------------------------------------
// Case 6: NO ctor declared, but members have ctors → NON-TRIVIAL implicit ctor
// ---------------------------------------------------------------
class F {
    std::string name_;             // std::string has a default ctor
    int count_ = 7;                // in-class initializer
public:
    // no ctor declared → implicit F() runs string's ctor and sets count_ = 7
    void dump() const { std::cout << "'" << name_ << "' " << count_ << "\n"; }
};

int main() {
    // Case 1: trivial default ctor — indeterminate members
    A a;                           // a.x, a.y are garbage
    A a2{};                        // value-init → a2.x == 0, a2.y == 0.0
    std::cout << "a2.x=" << a2.x << " a2.y=" << a2.y << "\n";  // 0 0

    // Case 2: no default ctor available
    // B b;                        // ERROR: no matching constructor
    B b(5);                        // OK
    (void)b;

    // Case 3: default ctor requested explicitly
    C c1;                          // OK: C() = default; v_ == 0
    C c2(9);                       // OK
    (void)c1; (void)c2;

    // Case 4: default ctor is deleted
    // D d;                        // ERROR: use of deleted function
    D d(1); (void)d;

    // Case 5: E must initialize its member
    E e; (void)e;                  // OK

    // Case 6: non-trivial implicit ctor
    F f;                           // OK: std::string default-constructed, count_ = 7
    f.dump();                      // prints: '' 7
}