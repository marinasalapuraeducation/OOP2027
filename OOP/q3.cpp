#include <iostream>
#include <stdexcept>
#include <string>

class Temperature {
private:
    double celsius_;                    // hidden representation

    // private helper: keeps the invariant in one place
    static void check(double c) {
        if (c < -273.15)
            throw std::invalid_argument("below absolute zero");
    }

public:
    explicit Temperature(double celsius = 0.0) : celsius_(celsius) {
        check(celsius_);
    }

    // Behavior-oriented interface, not raw field access
    void setCelsius(double c) { check(c); celsius_ = c; }
    double celsius() const { return celsius_; }

    double fahrenheit() const { return celsius_ * 9.0 / 5.0 + 32.0; }
    void setFahrenheit(double f) { setCelsius((f - 32.0) * 5.0 / 9.0); }

    void warmBy(double delta) {
        check(celsius_ + delta);
        celsius_ += delta;
    }
};

int q3() {
    Temperature t(20.0);

    t.warmBy(5.0);                       // goes through validation
    std::cout << t.celsius() << "\n"; // 25
    std::cout << t.fahrenheit() << "\n"; // 77

    try {
        t.setCelsius(-300.0);            // rejected: invariant preserved
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    // t.celsius_ = -300;                // ERROR: private member
}