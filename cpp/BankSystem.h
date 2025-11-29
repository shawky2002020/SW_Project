#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H
#include <vector>
#include "Customer.h"
#include "Admin.h"
#include "FileHandle.h"
#include "UIManager.h"

class BankSystem {
private:
    std::vector<Customer> allCustomers;
    std::vector<Admin> allAdmins;      
    User* currentUser;

    // Make constructor private to enforce singleton pattern
    BankSystem(); 
    BankSystem(const BankSystem&) = delete; // Prevent copy
    BankSystem& operator=(const BankSystem&) = delete; // Prevent assignment

public:
    // Singleton Accessor (Static Local Variable Pattern - Thread Safe C++11+)
    static BankSystem* getInstance();

    void run();
    bool authenticateUser(std::string user, std::string pass);
    void monitorActivity();
    
    void customerLoop(Customer* customer); 
    void adminLoop(Admin* admin);
    
    Customer* getCustomerByID(const std::string& id);
    
    // Dependencies
    FileHandle fileHandler;
};

#endif // BANKSYSTEM_H
