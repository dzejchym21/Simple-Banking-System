#ifndef SIMPLE_BANKING_SYSTEM_BANK_H
#define SIMPLE_BANKING_SYSTEM_BANK_H

#include <map>
#include "Account.h"

class Bank {
private:
    std::map<std::string, Account> accounts;
    int nextAccountNumber = 1000;
public:
    Bank() = default;
    void createAccount(const std::string& ownerName, double initialDeposit);
    bool depositTo(const std::string& accountNumber, double amount);
    bool withdrawFrom(const std::string& accountNumber, double amount);
    const std::map<std::string, Account>& getAccounts() const;
};


#endif
