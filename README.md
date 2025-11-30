# **Software Requirements Specification (SRS) – Bank Management System**

## **1. Introduction**

### **1.1 Purpose**
The purpose of this document is to define the requirements for the **Bank Management System (BMS)**, which enables customers to efficiently manage their bank accounts. The system provides features including deposits, withdrawals, fund transfers, bill payments, loan requests, and secure authentication.  
This document serves as a reference for developers, testers, and stakeholders to understand the system features, constraints, and expected behavior.

### **1.2 Scope**
The Bank Management System will allow customers to:
- Deposit and withdraw money with real-time balance updates.
- Transfer funds between accounts and pay common bills.
- Request loans and receive notifications of approval or rejection.
- Log in securely with protection against repeated failed login attempts.

The system is designed to run in a **console environment using C++ with Object-Oriented Programming principles**.  
All actions will include confirmation messages and input validation to ensure security, reliability, and usability.

### **1.3 Definitions, Acronyms, and Abbreviations**
| Term | Definition |
|------|------------|
| BMS | Bank Management System |
| UI | User Interface (Console) |
| OOP | Object-Oriented Programming |
| ID | Identification Number |

### **1.4 References**
- Functional Requirements Document (current document)
- Non-Functional Requirements Document (current document)
- C++ Programming Language Documentation

### **1.5 Overview**
This SRS document includes:
- Overall description of the system, including user characteristics, constraints, and assumptions.
- Detailed functional and non-functional requirements.
- Visual diagrams such as **Use Case Diagrams, Sequence Diagrams, and Activity Diagrams**.

---

## **2. Functional Requirements**

### **1. Deposit Money**
- The system shall allow customers to deposit money into their account and update the balance immediately.
- The system shall record each deposit with a transaction ID.

### **2. Withdraw Money**
- The system shall allow customers to withdraw money only if the balance is sufficient.
- The system shall update the balance instantly after withdrawal.

### **3. Check Account Balance**
- The system shall display the correct account balance within **2 seconds** after request.

### **4. Transfer Money**
- The system shall allow customers to transfer money to another account.
- The system shall display a confirmation message when the transfer is successful.

### **5. Log In / Authentication**
- The system shall allow users to log in using a username and password.
- The system shall block login access after **5 failed attempts**.

### **6. Edit Customer Information**
- The system shall allow customers to update their phone number or email address.
- The system shall save all changes immediately.

### **7. Delete Account**
- The system shall allow an admin to close a customer account **only if the balance is zero**.

### **8. Bill Payment**
- The system shall allow customers to pay common bills (e.g., electricity, water).
- The system shall show a success message when the payment is processed.

### **9. Loan Request**
- The system shall allow customers to request a loan using a simple form.
- The system shall notify the customer when the loan is approved or rejected.

### **10. View Customer Profile**
- The system shall display the customer’s full profile including:
  **Name, ID, Phone, Email, Balance, and Account Type**

### **11. Logout**
- The system shall allow users to safely log out after completing their activities.

---

## **3. Non-Functional Requirements**

### **1. Performance**
- The system shall respond to balance inquiries within **2 seconds**.
- The system shall complete money transfers within **3 seconds**.

### **2. Usability**
- The system shall provide a clear text-based menu interface.
- All successful operations (deposit, withdrawal, transfer, bill payment) shall display a confirmation message.

### **3. Reliability**
- The system shall validate all inputs to prevent system crashes due to invalid or unexpected data.
- The system shall save all data to files to ensure no loss of information after program exit.

### **4. Maintainability**
- The system shall follow object-oriented principles, including encapsulation and modular class structure.
- The source code shall separate core business logic (classes) from the user interface (menus).

---
