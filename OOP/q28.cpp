#include <iostream>

class Vector3D {
private:
    double x_, y_, z_;

public:
    Vector3D(double x = 0, double y = 0, double z = 0)
        : x_(x), y_(y), z_(z) {
    }

    // 1. Declaration of friend functions
    // These functions are NOT members, but they can access x_, y_, z_
    friend Vector3D operator+(const Vector3D& a, const Vector3D& b);
    friend std::ostream& operator<<(std::ostream& os, const Vector3D& v);
    friend class VectorTester; // A friend class
};

// 2. Definition of friend operator+
//    Notice it takes TWO parameters (unlike a member function, which takes one).
//    It can directly access a.x_, b.x_, etc.
Vector3D operator+(const Vector3D& a, const Vector3D& b) {
    return Vector3D(a.x_ + b.x_, a.y_ + b.y_, a.z_ + b.z_);
}

// 3. Definition of friend operator<< for printing
std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
    os << "(" << v.x_ << ", " << v.y_ << ", " << v.z_ << ")";
    return os;
}

// 4. A friend class
class VectorTester {
public:
    static void inspect(const Vector3D& v) {
        // Can access private members of Vector3D
        std::cout << "Inspection: x=" << v.x_ << " y=" << v.y_ << " z=" << v.z_ << "\n";
    }
};

int q28() {
    Vector3D v1(1.0, 2.0, 3.0);
    Vector3D v2(4.0, 5.0, 6.0);

    Vector3D v3 = v1 + v2;  // Calls friend operator+

    std::cout << "v1 = " << v1 << "\n"; // Calls friend operator<<
    std::cout << "v2 = " << v2 << "\n";
    std::cout << "v3 = " << v3 << "\n";

    VectorTester::inspect(v3); // Friend class accessing private data

    return 0;
}