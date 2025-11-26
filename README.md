# Banking System Console Application

## Overview
This is a **C++ console-based banking system** implemented using **Object-Oriented Programming (OOP)** principles.  
The system allows customers to create accounts, perform transactions, and manage their profile, while ensuring security, performance, and reliability. All data is stored in files (text or binary), with no external database required.

---

## Features

### Functional Requirements

1. **Create Account**
   - Customers can create a new account by entering basic information (name, ID, phone) in a single form.
   - New accounts are saved immediately after submission.

2. **Deposit Money**
   - Customers can deposit money into their account.
   - The balance updates immediately, and each deposit is recorded with a transaction ID.

3. **Withdraw Money**
   - Customers can withdraw money only if sufficient balance exists.
   - Balance updates instantly after withdrawal.

4. **Check Account Balance**
   - Displays the current account balance within 2 seconds.

5. **Transfer Money**
   - Allows customers to transfer money to another account.
   - Confirmation message shown after successful transfer.

6. **View Transaction History**
   - Lists all deposits, withdrawals, and transfers for the customer.
   - Each transaction includes the date, type, and amount.

7. **Log In / Authentication**
   - Users can log in with a username and password.
   - Login is blocked after 5 failed attempts.

8. **Edit Customer Information**
   - Customers can update their phone number or email.
   - Changes are saved immediately.

9. **Delete Account**
   - Admin can close a customer account if the balance is zero.

10. **Bill Payment**
    - Customers can pay common bills (electricity, water).
    - Success message displayed after payment.

11. **Loan Request**
    - Customers can request a loan via a simple form.
    - Notification sent on approval or rejection.

12. **Account Search**
    - Admin can search accounts by ID or name.

13. **View Customer Profile**
    - Displays full profile including name, ID, phone, email, balance, and account type.

14. **Account Types**
    - Supports different account types (Savings / Checking) with minimum balance rules.

15. **Logout**
    - Users are logged out after 15 minutes of inactivity.

---

### Non-Functional Requirements

1. **Performance**
   - Balance inquiries respond within 2 seconds.
   - Money transfers complete within 3 seconds.

2. **Security**
   - Password input is hidden.
   - Passwords are encrypted.
   - Accounts locked for 5 minutes after 5 failed login attempts.

3. **Usability**
   - Clear text-based menu interface.
   - Confirmation messages shown for successful operations.

4. **Reliability**
   - All inputs validated to prevent crashes.
   - Data saved to files to prevent loss after program exit.

5. **Maintainability**
   - Follows OOP principles: encapsulation and modular classes.
   - Logic separated from UI.

---

### Constraints
- Implemented in **C++** using OOP principles.
- Runs in a **console environment**.
- Data stored in **text or binary files** (no database).

---

## Getting Started

### Requirements
- C++ compiler (e.g., `g++`)
- Console / terminal environment

### Compilation
```bash
g++ main.cpp -o BankingSystem
