#include "BankSystem.h"
#include "Customer.h"
#include "Admin.h"
#include "Account.h"
#include "Transaction.h"
#include "UIManager.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <limits> 

using namespace std;

// --- Utility Implementation (Placeholders) ---

// FIX: Must be static to be callable without an object instance
string User::hash(string pass) {
    return "hashed_" + pass + "_secured";
}

// UIManager Implementation 
void UIManager::displayLogin() { cout << "\n--- Bank Login ---\n"; }
void UIManager::displayMainMenu() { cout << "\n--- Main Menu --\n"; }
void UIManager::displayCustomerMenu() {
    cout << "\n--- Customer Actions ---\n";
    cout << "1. Check Account Balance\n";
    cout << "2. Deposit Money\n";
    cout << "3. Withdraw Money\n";
    cout << "4. Transfer Money\n";
    cout << "5. View Transaction History\n";
    cout << "6. Pay Bill\n";
    cout << "7. View Profile\n";
    cout << "8. Logout\n";
    cout << "------------------------\n";
}

int UIManager::getCustomerChoice() {
    int choice;
    cout << "Enter your choice: ";
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1; 
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

string UIManager::getInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

string UIManager::getCredential(const string& prompt) {
    string input;
    cout << prompt;
    cin >> input; 
    return input;
}

double UIManager::getAmountInput(const string& prompt) {
    double amount;
    cout << prompt;
    while (!(cin >> amount) || amount <= 0) {
        cout << "Invalid amount. Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return amount;
}

void UIManager::showError(const string& msg) { cout << "[ERROR] " << msg << endl; }
void UIManager::showSuccess(const string& msg) { cout << "[SUCCESS] " << msg << endl; }

// FileHandle Implementation (omitted for brevity)
void FileHandle::saveCustomers(const vector<Customer>& customers) {
    cout << "[FILE] Saving " << customers.size() << " customers to file...\n";
}

vector<Customer> FileHandle::loadCustomers() {
    cout << "[FILE] Loading customer data...\n";
    
    vector<Customer> customers;
    customers.emplace_back("user1", "pass1", "Jane Doe", "12345"); 
    
    Account* initialAcc = new Account("ACC-001", "2025-01-01", 1000.00); 
    customers.back().addAccount(initialAcc);
    
    return customers; 
}
void FileHandle::logTransaction(const Transaction& transaction) {
    // Note: This function calls BankSystem::getInstance()
}

// --- Entity Implementation (omitted for brevity) ---

// Transaction 
Transaction::Transaction(string id, double amt, TransactionType t) 
    : transactionID(id), amount(amt), type(t) 
{
    time_t now = time(0);
    timestamp = ctime(&now);
}

string Transaction::getDetails() const {
    stringstream ss;
    ss << "ID: " << transactionID << " | Type: ";
    switch(type) {
        case TransactionType::DEPOSIT: ss << "DEPOSIT"; break;
        case TransactionType::WITHDRAWAL: ss << "WITHDRAWAL"; break;
        case TransactionType::TRANSFER: ss << "TRANSFER"; break;
        case TransactionType::BILL_PAYMENT: ss << "BILL_PAYMENT"; break;
    }
    ss << " | Amount: $" << amount << " | Date: " << timestamp;
    return ss.str();
}

// Account
Account::Account(string num, string date, double initialBalance) 
    : accountNumber(num), creationDate(date), balance(initialBalance) {}

void Account::recordTransaction(double amount, TransactionType type) {
    string id = to_string(transactions.size() + 1000); 
    transactions.emplace_back(id, amount, type);
    BankSystem::getInstance()->fileHandler.logTransaction(transactions.back());
}

void Account::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        recordTransaction(amount, TransactionType::DEPOSIT);
        UIManager::showSuccess("Deposit successful. New balance: $" + to_string(balance));
    } else {
        UIManager::showError("Deposit amount must be positive.");
    }
}

void Account::withdraw(double amount) {
    if (amount > 0 && balance >= amount) {
        balance -= amount;
        recordTransaction(amount, TransactionType::WITHDRAWAL);
        UIManager::showSuccess("Withdrawal successful. New balance: $" + to_string(balance));
    } else {
        UIManager::showError("Insufficient funds or invalid amount.");
    }
}

bool Account::transfer(Account& to, double amount) {
    if (amount > 0 && balance >= amount) {
        balance -= amount;
        recordTransaction(amount, TransactionType::TRANSFER);

        to.balance += amount;
        to.recordTransaction(amount, TransactionType::TRANSFER);
        
        UIManager::showSuccess("Transfer of $" + to_string(amount) + " successful.");
        return true;
    }
    UIManager::showError("Transfer failed. Insufficient funds or invalid amount.");
    return false;
}

double Account::checkBalance() const {
    return balance;
}

bool Account::payBill(string billType, double amount) {
    if (amount > 0 && balance >= amount) {
        balance -= amount;
        recordTransaction(amount, TransactionType::BILL_PAYMENT);
        UIManager::showSuccess("Bill payment for " + billType + " successful. New balance: $" + to_string(balance));
        return true;
    }
    UIManager::showError("Bill payment failed. Insufficient funds.");
    return false;
}

// User (Abstract Base)
User::User(string user, string pass) : username(user), failedLoginAttempts(0), isLocked(false) {
    passwordHash = hash(pass);
}

void User::logout() {
    cout << "User " << username << " logged out.\n";
}

void User::changePassword(string newPass) {
    passwordHash = hash(newPass);
    UIManager::showSuccess("Password changed successfully.");
}


// Customer
Customer::Customer(string user, string pass, string name, string id)
    : User(user, pass), fullName(name), nationalID(id) {}

bool Customer::login(string user, string pass) {
    if (username == user && passwordHash == hash(pass) && !isLocked) {
        failedLoginAttempts = 0;
        return true;
    }
    if (isLocked) { UIManager::showError("Account is locked due to too many failed attempts."); return false; }
    failedLoginAttempts++;
    if (failedLoginAttempts >= 5) { isLocked = true; UIManager::showError("Account locked. Too many failed attempts."); }
    return false;
}

void Customer::updateContactInfo(string phone, string mail) {
    phoneNumber = phone;
    email = mail;
    UIManager::showSuccess("Contact information updated.");
}

void Customer::viewProfile() const {
    cout << "\n--- Customer Profile ---\n";
    cout << "Name: " << fullName << endl;
    cout << "ID: " << nationalID << endl;
    cout << "Phone: " << (phoneNumber.empty() ? "N/A" : phoneNumber) << endl;
    cout << "Email: " << (email.empty() ? "N/A" : email) << endl;
    cout << "Total Accounts: " << getAccounts().size() << endl; 
    if (getAccounts().empty()) {
        cout << "No accounts linked.\n";
    } else {
        cout << "--- Account Summary ---\n";
        for (size_t i = 0; i < getAccounts().size(); ++i) { 
            cout << "  [" << i+1 << "] Number: " << getAccounts()[i]->getAccountNumber() 
                 << ", Balance: $" << getAccounts()[i]->checkBalance() << endl;
        }
    }
}

void Customer::requestLoan() {
    UIManager::showSuccess("Loan request submitted for " + fullName + ".");
}

void Customer::addAccount(Account* acc) {
    accounts.push_back(acc);
}

Account* Customer::getAccount(string accNum) {
    for (Account* acc : accounts) {
        if (acc->getAccountNumber() == accNum) {
            return acc;
        }
    }
    return nullptr;
}

Account* Customer::getPrimaryAccount() {
    if (accounts.empty()) return nullptr;
    return accounts[0]; 
}


// Admin (omitted for brevity)
Admin::Admin(string user, string pass, string id) : User(user, pass), adminID(id) {}

bool Admin::login(string user, string pass) {
    if (username == user && passwordHash == hash(pass) && !isLocked) {
        failedLoginAttempts = 0;
        return true;
    }
    if (isLocked) { UIManager::showError("Account is locked due to too many failed attempts."); return false; }
    failedLoginAttempts++;
    if (failedLoginAttempts >= 5) { isLocked = true; UIManager::showError("Account locked. Too many failed attempts."); }
    return false;
}

void Admin::createAccount() {
    cout << "Admin is creating a new customer account...\n";
}
void Admin::closeAccount() {
    cout << "Admin is attempting to close an account...\n";
}
void Admin::searchAccount() {
    cout << "Admin is searching for customer account...\n";
}


// --- Controller Implementation ---

// BankSystem Constructor
BankSystem::BankSystem() {
    allCustomers = fileHandler.loadCustomers();
    allAdmins.emplace_back("admin", "adminpass", "A101");
}

// BankSystem Singleton Accessor
BankSystem* BankSystem::getInstance() {
    static BankSystem instance; 
    return &instance;
}

bool BankSystem::authenticateUser(string user, string pass) {
    for (Admin& admin : allAdmins) {
        if (admin.login(user, pass)) {
            currentUser = &admin;
            return true;
        }
    }
    for (Customer& customer : allCustomers) {
        if (customer.login(user, pass)) {
            currentUser = &customer;
            return true;
        }
    }
    UIManager::showError("Authentication failed or account is locked.");
    return false;
}

void BankSystem::run() {
    UIManager::displayLogin();
    
    string user = UIManager::getInput("Enter username: "); 
    string pass = UIManager::getInput("Enter password: ");

    if (authenticateUser(user, pass)) {
        UIManager::showSuccess("Login successful!");
        
        if (dynamic_cast<Customer*>(currentUser)) {
            customerLoop(static_cast<Customer*>(currentUser));
        } else if (dynamic_cast<Admin*>(currentUser)) {
            UIManager::showSuccess("Welcome, Admin!");
        }
    }
    if (!allCustomers.empty()) {
        fileHandler.saveCustomers(allCustomers);
    }
}

void BankSystem::customerLoop(Customer* customer) {
    bool running = true;
    while (running) {
        UIManager::displayCustomerMenu();
        int choice = UIManager::getCustomerChoice(); 

        Account* acc = customer->getPrimaryAccount();
        if (!acc) {
            UIManager::showError("No primary account found. Cannot perform actions.");
            return;
        }
        
        switch (choice) {
            case 1: // Check Balance
                cout << "\nYour current balance for " << acc->getAccountNumber() << " is: $" << acc->checkBalance() << endl;
                break;
            case 2: { // Deposit
                double amount = UIManager::getAmountInput("Enter deposit amount: $");
                acc->deposit(amount);
                break;
            }
            case 3: { // Withdraw
                double amount = UIManager::getAmountInput("Enter withdrawal amount: $");
                acc->withdraw(amount);
                break;
            }
            case 4: { // Transfer (Simplified: Transfer to a hardcoded external account)
                string targetNum = UIManager::getInput("Enter target account number (e.g., ACC-999): ");
                double amount = UIManager::getAmountInput("Enter transfer amount: $");
                
                Account targetAcc(targetNum, "External");
                targetAcc.deposit(0.01); 
                acc->transfer(targetAcc, amount);
                break;
            }
            case 5: { // View Transaction History
                cout << "\n--- Transaction History for " << acc->getAccountNumber() << " ---\n";
                const auto& history = acc->getTransactions();
                if (history.empty()) {
                    cout << "No transactions recorded.\n";
                } else {
                    for (const auto& tx : history) {
                        cout << tx.getDetails();
                    }
                }
                cout << "-------------------------------------------\n";
                break;
            }
            case 6: { // Pay Bill
                string billType = UIManager::getInput("Enter bill type (e.g., electricity): ");
                double amount = UIManager::getAmountInput("Enter bill amount: $");
                acc->payBill(billType, amount);
                break;
            }
            case 7: // View Profile
                customer->viewProfile();
                break;
            case 8: // Logout
                customer->logout();
                running = false;
                break;
            default:
                UIManager::showError("Invalid choice. Please try again.");
        }
    }
}

void BankSystem::monitorActivity() {
    cout << "Activity monitoring is running...\n";
}
