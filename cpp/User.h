#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

// Corresponds to the <<Abstract>> User class
class User {
protected:
    std::string username;
    std::string passwordHash;
    int failedLoginAttempts;
    bool isLocked;

public:
    // Constructor
    User(std::string user, std::string pass);
    
    // Virtual destructor required for base class
    virtual ~User() = default;

    // Methods from diagram
    virtual bool login(std::string user, std::string pass) = 0;             // +login(string user, string pass) - Pure virtual
    virtual void logout();                                                  // +logout()
    void changePassword(std::string newPass);                               // +changePassword(string newPass)

    // Accessors (getters)
    std::string getUsername() const { return username; }
    bool getIsLocked() const { return isLocked; }

protected:
    std::string hash(std::string pass); // Placeholder for hashing logic
};

#endif // USER_H
