#include <iostream>
#include <vector>

// 1. Trivial default ctor: members are indeterminate
struct Trivial {
	int x;
	double y;
};

// 2. In-class initializers → safe defaults with = default
class Safe {
public:
	Safe() = default;                 // uses the initializers below
	void dump() const {
		std::cout << "retries=" << retries_
			<< " timeout=" << timeout_
			<< " verbose=" << verbose_ << "\n";
	}
private:
	int    retries_ = 3;
	double timeout_ = 1.5;
	bool   verbose_ = false;
};

// 3. Deleted default ctor: must always supply a resource
class FileHandle {
public:
	FileHandle() = delete;            // forbid default construction
	explicit FileHandle(int fd) : fd_(fd) {}
	int fd() const { return fd_; }
private:
	int fd_;
};

// 4. Default ctor must initialize a member that lacks one
class Member { public: explicit Member(int v) : v_(v) {} int v_; };

					 class Owner {
						 Member m_;
					 public:
						 Owner() : m_(42) {}               // required: Member has no default ctor
						 int value() const { return m_.v_; }
					 };

					 int main() {
						 // --- trivial vs value-initialization ---
						 Trivial a;                        // a.x, a.y indeterminate
						 Trivial b{};                      // b.x == 0, b.y == 0.0
						 std::cout << "b.x=" << b.x << " b.y=" << b.y << "\n";

						 // --- in-class initializers via = default ---
						 Safe s;
						 s.dump();                         // retries=3 timeout=1.5 verbose=0

						 // --- deleted default ctor ---
						 // FileHandle f;                  // ERROR: deleted
						 FileHandle f(7);                  // OK
						 std::cout << "fd=" << f.fd() << "\n";

						 // --- member without default ctor ---
						 Owner o;
						 std::cout << "owner member=" << o.value() << "\n";  // 42

						 // --- containers use the default ctor ---
						 std::vector<Safe> v(3);           // three default-constructed Safe objects
						 std::cout << "vector size=" << v.size() << "\n";
					 }