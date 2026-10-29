class Base {
public:
    virtual ~Base() = default;   // обязательно
    virtual void f() {}
};
class Derived : public Base {
    int* data_ = new int[100];
public:
    ~Derived() override { delete[] data_; }
};

Base* p = new Derived;
delete p;   // без virtual ~Base() — UB; с ним — корректно вызовется ~Derived