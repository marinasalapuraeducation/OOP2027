class T {
public:
    T();                     // 0 args
    T(int);                  // 1 int
    T(int, double);          // int + double
    T(double, int);          // double + int  — different order, OK
    T(const std::string&);   // string
};