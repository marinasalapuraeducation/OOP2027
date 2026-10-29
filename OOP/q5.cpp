#include <iostream>
#include <memory>
#include <vector>

// ---- Common interface (abstract base) ----
class Shape {
public:
    virtual ~Shape() = default;          // virtual dtor for safe deletion
    virtual double area() const = 0;     // pure virtual: must be overridden
    virtual const char* name() const = 0;
};

// ---- Concrete implementations ----
class Circle : public Shape {
    double r_;
public:
    explicit Circle(double r) : r_(r) {}
    double area() const override { return 3.14159 * r_ * r_; }
    const char* name() const override { return "Circle"; }
};

class Square : public Shape {
    double s_;
public:
    explicit Square(double s) : s_(s) {}
    double area() const override { return s_ * s_; }
    const char* name() const override { return "Square"; }
};

class Triangle : public Shape {
    double b_, h_;
public:
    Triangle(double b, double h) : b_(b), h_(h) {}
    double area() const override { return 0.5 * b_ * h_; }
    const char* name() const override { return "Triangle"; }
};

// ---- Caller knows only the Shape interface ----
void report(const std::vector<std::unique_ptr<Shape>>& shapes) {
    for (const auto& s : shapes)
        std::cout << s->name() << ": area = " << s->area() << "\n";
}

int q5() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(2.0));
    shapes.push_back(std::make_unique<Square>(3.0));
    shapes.push_back(std::make_unique<Triangle>(4.0, 5.0));

    report(shapes);
    // Circle:   area = 12.5664
    // Square:   area = 9
    // Triangle: area = 10

    // Substitutability: base reference to a derived object
    const Shape& ref = *shapes[0];
    std::cout << ref.name() << "\n";      // Circle — dynamic dispatch
}