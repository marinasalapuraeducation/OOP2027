class BankAccount {
    int ID; // Warning: This will be uninitialized if not given a value!
public:
    BankAccount() = default;       // Restores the default constructor
    BankAccount(int ID) : ID(ID) {}
};
void q35() {
    BankAccount bankAccount1(12345);
}

//These errors mean exactly what they say : You are trying to create an object without passing any arguments(which requires a default constructor), but the class does not have one.