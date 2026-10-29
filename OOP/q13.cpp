class T {
public:
    T() {}          // OK: no return type, returns nothing
    // int T() { }   // ERROR: constructors cannot have a return type
    // void T() { }  // ERROR: even void is forbidden
};