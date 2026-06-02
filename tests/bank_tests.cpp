#include <gtest/gtest.h>
#include "bank.h"

class BankTestFixture : public ::testing::Test {
protected:
    Bank bank;

    void SetUp() override {
        bank.createAccount("Jan Kowalski", 500.0);
    }

};

TEST_F(BankTestFixture, CreatesAccountWithCorrectValues) {
    ASSERT_EQ(1, bank.getAccounts().size());

    auto it = bank.getAccounts().begin();
    ASSERT_EQ("Jan Kowalski", it->second.getOwnerName());
    ASSERT_EQ(500.0, it->second.getBalance());
}

TEST_F(BankTestFixture, DepositToAddsCorrectly) {
    auto it = bank.getAccounts().begin();
    ASSERT_EQ(500.0, it->second.getBalance());
    ASSERT_TRUE(bank.depositTo("1000", 300));
    ASSERT_EQ(800.0, it->second.getBalance());
}

TEST_F(BankTestFixture, WithdrawFromEnoughBalance) {
    auto it = bank.getAccounts().begin();
    ASSERT_EQ(500.0, it->second.getBalance());
    ASSERT_TRUE(bank.withdrawFrom("1000", 300));
    ASSERT_EQ(200.0, it->second.getBalance());
}

TEST_F(BankTestFixture, WithdrawFromNotEnoughBalance) {
    auto it = bank.getAccounts().begin();
    ASSERT_EQ(500.0, it->second.getBalance());
    ASSERT_FALSE(bank.withdrawFrom("1000", 800));
    ASSERT_EQ(500.0, it->second.getBalance());
}

TEST_F(BankTestFixture, OperationsOnNonExistentAccountFail) {
    ASSERT_FALSE(bank.depositTo("9999", 100.0));
    ASSERT_FALSE(bank.withdrawFrom("9999", 100.0));
}

TEST_F(BankTestFixture, PreventNegativeAmounts) {
    auto it = bank.getAccounts().begin();

    ASSERT_FALSE(bank.depositTo("1000", -100.0));
    ASSERT_EQ(500.0, it->second.getBalance());

    ASSERT_FALSE(bank.withdrawFrom("1000", -50.0));
    ASSERT_EQ(500.0, it->second.getBalance());
}