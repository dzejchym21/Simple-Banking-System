#include "Account.h"

Account::Account(const std::string& num, const std::string& owner, double bal): accountNumber(num), ownerName(owner), balance(bal) {}

void Account::deposit(double amount) {
    balance += amount;
}

bool Account::withdraw(double amount) {
    if (balance < amount) {
        return false;
    }
    balance -= amount;
    return true;
}

const std::string& Account::getAccountNumber() const {
    return accountNumber;
}

const std::string& Account::getOwnerName() const {
    return ownerName;
}

double Account::getBalance() const {
    return balance;
}