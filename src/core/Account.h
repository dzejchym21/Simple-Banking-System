#ifndef SIMPLE_BANKING_SYSTEM_ACCOUNT_H
#define SIMPLE_BANKING_SYSTEM_ACCOUNT_H

#include <string>

class Account {
private:
    std::string accountNumber;
    std::string ownerName;
    double balance = 0.0;
public:
    Account() = default;
    Account(const std::string& num, const std::string& owner, double bal);
    void deposit(double amount);
    bool withdraw(double amount);
    const std::string& getAccountNumber() const;
    const std::string& getOwnerName() const;
    double getBalance() const;
};


#endif
