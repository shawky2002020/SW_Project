#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <vector>
#include "User.h"
#include "Account.h"

class Customer : public User
{
private:
    std::string fullName;
    std::string nationalID;
    std::string phoneNumber;
    std::string email;
    std::vector<Account *> accounts; // owns relationship (1..*)

public:
    // Constructor
    Customer(std::string user, std::string pass, std::string name, std::string id);

    // Overridden login method
    bool login(std::string user, std::string pass) override;

    // Methods from diagram
    void updateContactInfo(std::string phone, std::string mail); // +updateContactinfo()
    void viewProfile() const;                                    // +viewProfile()
    void requestLoan();                                          // +requestLoan()
    // In Customer.h (Public section)
    Account *getPrimaryAccount(); // NEW: Primary account accessor
    // Account management
    void addAccount(Account *acc);
    Account *getAccount(std::string accNum);

    // Accessors
    std::string getID() const { return nationalID; }
    std::string getName() const { return fullName; }
    const std::vector<Account *> &getAccounts() const { return accounts; }

    // Note: Must handle memory management for Account*
};

#endif // CUSTOMER_H
