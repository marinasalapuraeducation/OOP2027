#include <iostream>
#include <string>

// Простая запись: нет инвариантов, все поля публичны, нет логики
//struct уместен — простой агрегат
struct Point {
    double x = 0.0;
    double y = 0.0;
};

double distance(const Point& a, const Point& b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

int q81() {
    Point p{ 1.0, 2.0 };          // aggregate initialization
    Point q{ 4.0, 6.0 };
    std::cout << distance(p, q) << "\n";  // 5
}


#include <iostream>
#include <stdexcept>

// Есть инвариант: радиус всегда > 0. Нужно скрыть состояние.
//class уместен — есть инвариант
class Circle {
private:
    double radius_;

    static void check(double r) {
        if (r <= 0) throw std::invalid_argument("radius must be > 0");
    }

public:
    explicit Circle(double r) : radius_(r) { check(r); }

    void setRadius(double r) { check(r); radius_ = r; }
    double radius() const { return radius_; }
    double area()   const { return 3.14159 * radius_ * radius_; }
};

int q82() {
    Circle c(2.0);
    std::cout << c.area() << "\n";   // 12.5664

    try { c.setRadius(-1.0); }       // отклонено: инвариант защищён
    catch (const std::exception& e) { std::cout << e.what() << "\n"; }

    // c.radius_ = -1;               // ERROR: private
}