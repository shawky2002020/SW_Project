#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include <iostream>
#include "Transaction.h"

// Note: The diagram shows 'Accoun' (likely a typo for 'Account') as a concrete class.
class Account {
private:
    std::string accountNumber;
    double balance;
    std::string creationDate;
    std::vector<Transaction> transactions; // logs relationship

public:
    // Constructor (Defaulting to 0 balance)
    Account(std::string num, std::string date,double initialBalance = 0.0);

    // Methods from diagram
    void deposit(double amount);                                             // +deposit(double amount)
    virtual void withdraw(double amount);                                    // +withdraw(double amount)
    virtual bool transfer(Account& to, double amount);                       // +transfer(Account to, double amount)
    double checkBalance() const;                                             // +checkBalance() : double
    bool payBill(std::string billType, double amount);                       // +payBill(string billType, double amount)
    
    // Accessors
    std::string getAccountNumber() const { return accountNumber; }
    const std::vector<Transaction>& getTransactions() const { return transactions; }

protected:
    void recordTransaction(double amount, TransactionType type);
};

#endif // ACCOUNT_H
