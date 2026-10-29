// Class Constructor in C++ — What It Is and Features of Use

// 1. Member initializer list(preferred over assignment in the body)

class Point {
    int x_, y_;
public:
    Point(int x, int y) : x_(x), y_(y) {}   // initialization, not assignment
};

// 2. Order of initialization


class A {
    int b_;    // declared first  → initialized first
    int a_;    // declared second → initialized second
public:
    A(int v) : a_(v), b_(a_) {}  // WARNING: b_ initialized before a_ → b_ is garbage!
};


// 3. `explicit` to prevent accidental implicit conversions

class Vec {
public:
    explicit Vec(int n) : n_(n) {}   // Vec v = 5;  → ERROR (good)
private:
    int n_;
};

// 4. Delegating constructors

class Rect {
    int w_, h_;
public:
    Rect(int w, int h) : w_(w), h_(h) {}
    Rect() : Rect(1, 1) {}           // delegates to Rect(int,int)
};

// 5. Copy and move constructors

class Buffer {
    int* data_;
    std::size_t size_;
public:
    Buffer(std::size_t n) : data_(new int[n]), size_(n) {}
    ~Buffer() { delete[] data_; }

    Buffer(const Buffer& o)                       // copy: deep copy
        : data_(new int[o.size_]), size_(o.size_) {
        std::copy(o.data_, o.data_ + size_, data_);
    }

    Buffer(Buffer&& o) noexcept                   // move: steal pointer
        : data_(o.data_), size_(o.size_) {
        o.data_ = nullptr; o.size_ = 0;
    }
};


// 6. Constructors and inheritance

class Base { public: Base(int x) {} };
class Derived : public Base {
public:
    Derived() : Base(0) {}                  // or call explicitly
};

// 7. Constructor cannot be `virtual`, but can be `constexpr`/`noexcept`

// 8. Aggregate initialization vs.constructors

// 9. `= default` and `= delete`


class T {
public:
    T() = default;                  // ask compiler to generate
    T(const T&) = delete;           // forbid copying
};

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

class BankAccount {
private:
    std::string owner_;
    double balance_ = 0.0;
    const int id_;                       // const member → must be in init list

    static void check(double b) {
        if (b < 0) throw std::invalid_argument("negative balance");
    }

public:
    // 1. Parameterized constructor + member initializer list
    BankAccount(std::string owner, double initial, int id)
        : owner_(std::move(owner)), balance_(initial), id_(id) {
        check(balance_);                 // invariant enforced at construction
        std::cout << "ctor: " << owner_ << " id=" << id_ << "\n";
    }

    // 2. Delegating constructor
    BankAccount(std::string owner, int id)
        : BankAccount(std::move(owner), 0.0, id) {
    }

    // 3. Copy constructor (deep copy of string is automatic; shown for clarity)
    BankAccount(const BankAccount& o)
        : owner_(o.owner_), balance_(o.balance_), id_(o.id_) {
        std::cout << "copy ctor\n";
    }

    // 4. Move constructor
    BankAccount(BankAccount&& o) noexcept
        : owner_(std::move(o.owner_)), balance_(o.balance_), id_(o.id_) {
        o.balance_ = 0.0;
        std::cout << "move ctor\n";
    }

    ~BankAccount() { std::cout << "dtor: " << owner_ << "\n"; }

    void deposit(double a) {
        if (a <= 0) throw std::invalid_argument("bad amount");
        balance_ += a;
    }
    double balance() const { return balance_; }
    const std::string& owner() const { return owner_; }
};

int q11() {
    BankAccount a("Alice", 100.0, 1);    // parameterized ctor
    BankAccount b("Bob", 2);             // delegating ctor → balance 0
    BankAccount c = a;                   // copy ctor
    BankAccount d = std::move(a);        // move ctor

    b.deposit(50.0);
    std::cout << b.owner() << ": " << b.balance() << "\n";   // Bob: 50

    try {
        BankAccount bad("Eve", -5.0, 3); // throws in ctor → object never exists
    }
    catch (const std::exception& e) {
        std::cout << "caught: " << e.what() << "\n";
    }
}