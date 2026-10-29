// The Scope Resolution Operator `::` in C++ — Uses and Overloading


//The** scope resolution operator** `::` specifies the** scope** (or context) in which a name is looked up.It tells the compiler exactly* where* to find an identifier, resolving ambiguities between names that exist in multiple scopes.

// 1. Accessing global variables hidden by local / class variables

int value = 100;            // global

class Widget {
public:
	int value = 5;          // class member
	void show() {
		int value = 1;      // local
		std::cout << value << "\n"; // 1  (local)
		std::cout << this->value << "\n"; // 5  (member)
		std::cout << ::value << "\n"; // 100 (global via ::)
	}
};


// 2. Defining class member functions outside the class body

class Circle {
public:
	double area() const;    // declaration
};

double Circle::area() const { return 3.14 * 5 * 5; } // definition via ::

//### 3. Accessing static members of a class

class Counter {
public:
	static int count;
	static void reset() { count = 0; }
};
int Counter::count = 0;     // definition of static member

// Usage:
Counter::count = 10;
Counter::reset();

// 4. Accessing members of a base class (when hidden by derived class)

class Base {
public:
	void hello() { std::cout << "Base\n"; }
};

class Derived : public Base {
public:
	void hello() { std::cout << "Derived\n"; }
	void callBase() {
		Base::hello();      // explicitly call base version
	}
};

// 5. Accessing names in namespaces

namespace Math {
	double pi = 3.14159;
	double square(double x) { return x * x; }
}

int q25() {
	double p = Math::pi;                 // access namespace member
	double s = Math::square(4.0);        // call namespace function
}


// 6. Global namespace qualification(leading `::`)

//A leading `::` forces lookup in the** global namespace**, bypassing any local or class scope.

void print() { std::cout << "global\n"; }

namespace MyLib {
	void print() { std::cout << "MyLib\n"; }
	void test() {
		print();        // MyLib::print
		::print();      // global print()
	}
}
// 7. Resolving ambiguity in multiple inheritance

class A { public: void f() {} };
class B { public: void f() {} };
				class C : public A, public B {};

				// C obj; obj.f();    // ERROR: ambiguous
				// obj.A::f();        // OK: explicitly choose A's f()
				// obj.B::f();        // OK: choose B's f()

					//8. Accessing enumerators of a scoped enum (C++11 `enum class`)

				enum class Color { Red, Green, Blue };
				Color c = Color::Red;       // must use ::


				// Can `::` be overloaded ?

			//	**No.The scope resolution operator `: : ` cannot be overloaded.**


#include <iostream>

						// --- 1. Global variable ---
				int count = 0;

				namespace App {
					int count = 10;             // namespace-level variable

					// --- 2. Class with static members and hidden base method ---
					class Base {
					public:
						static int instances;
						void info() const { std::cout << "Base::info\n"; }
					};
					int Base::instances = 0;    // definition using ::

					class Derived : public Base {
					public:
						// --- 3. Member function defined outside (inline here for brevity) ---
						void info() const { std::cout << "Derived::info\n"; }
						void callBase() const { Base::info(); }  // 4. explicit base call
					};

					void demo() {
						int count = 99;                       // local variable

						std::cout << count << "\n";  // 99  (local)
						std::cout << App::count << "\n";  // 10  (namespace)
						std::cout << ::count << "\n";  // 0   (global ::)

						Derived d;
						d.info();                             // Derived::info
						d.callBase();                         // Base::info via ::

						Base::instances++;                    // 3. static member via ::
						std::cout << "instances=" << Base::instances << "\n";
					}
				}

				// --- 5. Multiple inheritance disambiguation ---
class A { public: void f() { std::cout << "A::f\n"; } };
class B { public: void f() { std::cout << "B::f\n"; } };
				class C : public A, public B {};

				// --- 6. Scoped enum ---
				enum class Color { Red, Green, Blue };

				int main() {
					App::demo();

					C c;
					// c.f();           // ERROR: ambiguous
					c.A::f();           // A::f
					c.B::f();           // B::f

					Color col = Color::Red;                   // must use ::
					if (col == Color::Red) std::cout << "Red\n";

					// --- 7. Definition of a member function outside the class ---
					// (shown as declaration/definition split in the class above)
				}
