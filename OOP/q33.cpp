#include <iostream>
#include <string>

class Connection {
    std::string address_;
    bool is_open_ = false;

public:
    Connection(std::string addr) : address_(std::move(addr)), is_open_(true) {
        std::cout << "Connected to " << address_ << "\n";
    }

    // ❌ ERROR: Destructor cannot take arguments
    // ~Connection(const std::string& reason) { ... }

    // ✅ Standard destructor: takes no arguments, always runs
    ~Connection() {
        if (is_open_) {
            std::cout << "Destructor: Force closing connection to " << address_
                << " (no reason provided).\n";
        }
    }

    // ✅ Regular method to handle "cleanup with arguments"
    void close(const std::string& reason) {
        if (is_open_) {
            std::cout << "Closing connection to " << address_
                << ". Reason: " << reason << "\n";
            is_open_ = false;
        }
    }
};

int q33() {
    {
        Connection c1("192.168.1.1");
        // We want to close this connection gracefully with a reason
        c1.close("User logged out");
    } // c1 destructor runs here (sees is_open_ is false, does nothing)

    {
        Connection c2("10.0.0.5");
        // We forget to call close(). 
    } // c2 destructor runs here (forces closure)
}