#include <iostream>
#include <stdexcept>

//Это и есть смысл инкапсуляции : private закрывает доступ извне, но не от самого класса.

//Методы того же класса(включая static)	        Да
//Конструкторы / деструктор того же класса	    Да
//Дружественные функции / классы(friend)	    Да
//Производные классы	                        Нет(нужен protected)
//Внешний код, main(), свободные функции	    Нет

class BankAccount {
private:
    double balance_ = 0.0;
    int    pin_ = 0;

    // приватный вспомогательный метод
    void checkAmount(double a) const {
        if (a <= 0) throw std::invalid_argument("amount must be > 0");
    }

public:
    BankAccount(double initial, int pin) : balance_(initial), pin_(pin) {}

    // публичный метод обращается к private-данным и private-методу
    void deposit(double amount) {
        checkAmount(amount);          // OK: private метод
        balance_ += amount;           // OK: private данные
    }

    // статический метод тоже имеет доступ к private
    static BankAccount makeEmpty(int pin) {
        BankAccount acc(0.0, pin);
        acc.balance_ = 0.0;           // OK: private поле другого объекта
        return acc;
    }

    // метод получает ДРУГОЙ объект того же класса и читает его private-поле
    bool samePin(const BankAccount& other) const {
        return pin_ == other.pin_;    // OK: private другого экземпляра
    }

    // метод может изменять private-поле другого объекта
    void steal(BankAccount& other) {
        balance_ += other.balance_;   // OK
        other.balance_ = 0.0;         // OK
    }
};

int main() {
    BankAccount a(100.0, 1234);
    BankAccount b(50.0, 1234);

    a.deposit(25.0);                  // вызывает private checkAmount
    std::cout << a.samePin(b) << "\n"; // 1 — читает private b.pin_

    // a.balance_ = -1;               // ERROR: private извне
    // a.checkAmount(5);              // ERROR: private метод извне
}