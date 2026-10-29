#include <iostream>
#include <stdexcept>
#include <string>

class BankAccount {
private:                                  // ---- hidden implementation ----
    double balance_ = 0.0;
    std::string owner_;

    // private helper: only this class uses it
    void checkPositive(double amount) const {
        if (amount <= 0) throw std::invalid_argument("amount must be > 0");
    }

public:                                   // ---- exposed interface ----
    BankAccount(std::string owner, double initial)
        : owner_(std::move(owner)) {
        if (initial < 0) throw std::invalid_argument("negative initial");
        balance_ = initial;
    }

    void deposit(double amount) {
        checkPositive(amount);            // can call private helper
        balance_ += amount;
    }

    void withdraw(double amount) {
        checkPositive(amount);
        if (amount > balance_) throw std::runtime_error("insufficient funds");
        balance_ -= amount;
    }

    double balance() const { return balance_; }        // read-only accessor
    const std::string& owner() const { return owner_; }
};

int q7() {
    BankAccount acc("Alice", 100.0);

    acc.deposit(50.0);                    // OK: public method
    acc.withdraw(30.0);                   // OK
    std::cout << acc.balance() << "\n";   // 120  (public accessor)
    std::cout << acc.owner() << "\n";   // Alice

    // acc.balance_ = -999;               // ERROR: private member
    // acc.checkPositive(5);              // ERROR: private helper
    // acc.owner_ = "Bob";                // ERROR: private data
}