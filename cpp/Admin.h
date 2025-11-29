#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include <iostream>

class Admin : public User {
private:
    std::string adminID;

public:
    // Constructor
    Admin(std::string user, std::string pass, std::string id);
    
    // Overridden login method
    bool login(std::string user, std::string pass) override;

    // Methods from diagram (these would call BankSystem methods)
    void createAccount();                                                   // +createAccount()
    void closeAccount();                                                    // +closeAccount()
    void searchAccount();                                                   // +searchAccount()
    
    // Accessor
    std::string getAdminID() const { return adminID; }
};

#endif // ADMIN_H
