#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "Enums.h"

class Transaction {
private:
    std::string transactionID;
    std::string timestamp;
    double amount;
    TransactionType type;

public:
    // Constructor
    Transaction(std::string id, double amt, TransactionType t);

    // Logs relationship: getDetails() : string
    std::string getDetails() const;

    // Accessors for logging
    std::string getID() const { return transactionID; }
    double getAmount() const { return amount; }
    TransactionType getType() const { return type; }
    // Note: Timestamp is set internally upon construction/logging

};

#endif // TRANSACTION_H
