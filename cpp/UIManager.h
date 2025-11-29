#ifndef UIMANAGER_H
#define UIMANAGER_H
#include <string>
#include <iostream>
#include <limits> // Required for numeric input clearing

class UIManager {
public:
    std::string getCredential(const std::string& prompt);
public:
    // Display Functions
    static void displayLogin();
    static void displayMainMenu(); 
    static void displayCustomerMenu(); // NEW: Customer Actions Menu
    
    // Input Functions
    static int getCustomerChoice();
    static std::string getInput(const std::string& prompt);
    static double getAmountInput(const std::string& prompt);

    // Status Functions
    static void showError(const std::string& msg);
    static void showSuccess(const std::string& msg);
};
#endif // UIMANAGER_H
