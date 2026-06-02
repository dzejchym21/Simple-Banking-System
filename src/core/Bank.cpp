#include "Bank.h"
#include <iostream>

void Bank::createAccount(const std::string& owner, double initialDeposit) {
    std::string num = std::to_string(nextAccountNumber++);

    Account newAccount(num, owner, initialDeposit);
    accounts[num] = newAccount;
    std::cout << "Konto utworzone! Numer: " << num << std::endl;
}

bool Bank::depositTo(const std::string& accountNumber, double amount) {
    if (!accounts.contains(accountNumber) || amount < 0) {
        return false;
    }
    accounts[accountNumber].deposit(amount);
    return true;
}

bool Bank::withdrawFrom(const std::string& accountNumber, double amount) {
    if (!accounts.contains(accountNumber) || amount < 0) {
        return false;
    }
    return accounts[accountNumber].withdraw(amount);
}

const std::map<std::string, Account>& Bank::getAccounts() const{
    return accounts;
}