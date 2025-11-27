#ifndef FILEHANDLE_H
#define FILEHANDLE_H
#include <vector>
#include "Customer.h"
#include "Transaction.h"

class FileHandle { // uses relationship
public:
    // Placeholder functions for file I/O
    void saveCustomers(const std::vector<Customer>& customers);
    std::vector<Customer> loadCustomers();
    void logTransaction(const Transaction& transaction);
};
#endif // FILEHANDLE_H
