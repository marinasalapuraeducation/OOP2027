#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ---- Base class: common state + interface ----
class Animal {
public:
    explicit Animal(std::string name) : name_(std::move(name)) {
        std::cout << "Animal(" << name_ << ") constructed\n";
    }

    virtual ~Animal() {                 // virtual dtor: safe deletion via base ptr
        std::cout << "Animal(" << name_ << ") destroyed\n";
    }

    virtual void speak() const {        // overridable behavior
        std::cout << name_ << " makes a sound\n";
    }

    const std::string& name() const { return name_; }  // reused by all derived

protected:
    std::string name_;                  // accessible to derived classes
};

// ---- Derived class 1: extends + overrides ----
class Dog : public Animal {             // Dog IS-A Animal
public:
    using Animal::Animal;               // inherit constructor

    void speak() const override {       // specialize behavior
        std::cout << name_ << " says Woof\n";
    }

    void fetch() const {                // new behavior unique to Dog
        std::cout << name_ << " fetches the ball\n";
    }
};

// ---- Derived class 2 ----
class Cat : public Animal {
public:
    using Animal::Animal;

    void speak() const override {
        std::cout << name_ << " says Meow\n";
    }
};

// ---- Reuse via the base interface (no knowledge of derived types) ----
void chorus(const std::vector<std::unique_ptr<Animal>>& animals) {
    for (const auto& a : animals)
        a->speak();                     // dynamic dispatch at runtime
}

int q4() {
    std::vector<std::unique_ptr<Animal>> zoo;
    zoo.push_back(std::make_unique<Dog>("Rex"));
    zoo.push_back(std::make_unique<Cat>("Tom"));

    chorus(zoo);
    // Rex says Woof
    // Tom says Meow

    // Substitutability: Dog* / Dog& usable where Animal is expected
    Dog d("Buddy");
    d.fetch();                          // inherited name_ + own behavior

    Animal& ref = d;                    // base reference to derived object
    ref.speak();                        // Buddy says Woof  (virtual call)
}