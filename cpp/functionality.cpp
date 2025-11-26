#include <iostream>
#include <string>
using namespace std;

class BankAccount
{
private:
  string accountHolder;
  int accountNumber;
  double balance;

  static int counter;
  static int nextID;

public:
  BankAccount()
      : accountHolder("Unknown"), balance(0), accountNumber(++nextID)
  {
    counter++;
    cout << "Default constructor called for Account #" << accountNumber << endl;
    cout << "Initial Balance: " << balance << endl;
  }

  BankAccount(const string &name, const double &initialBalance)
      : accountHolder(name), balance(initialBalance), accountNumber(++nextID)
  {
    counter++;
    cout << "Parameterized constructor called for Account #" << accountNumber << endl;
    cout << "Initial Balance: " << balance << endl;
  }

  BankAccount(const string &name)
      : accountHolder(name), balance(0), accountNumber(++nextID)
  {
    counter++;
    cout << "Parameterized constructor called for Account #" << accountNumber << endl;
    cout << "Initial Balance: " << balance << endl;
  }

  BankAccount(const BankAccount &) = delete;
  BankAccount &operator=(const BankAccount &) = delete;

  BankAccount(BankAccount &&other) noexcept
      : accountHolder(other.accountHolder), balance(other.balance), accountNumber(other.accountNumber)
  {
    other.balance = 0;
    other.accountHolder = "Moved";
    other.accountNumber = -1;
    cout << "Move constructor called for Account #" << accountNumber << endl;
  }

  BankAccount &operator=(BankAccount &&other) noexcept
  {
    if (this != &other)
    {
      accountHolder = other.accountHolder;
      balance = other.balance;
      accountNumber = other.accountNumber;

      other.balance = 0;
      other.accountHolder = "Moved";
      other.accountNumber = -1;
    }
    return *this;
  }

  ~BankAccount()
  {
    cout << "Destructor called for Account #" << accountNumber << endl;
  }

  BankAccount &deposit(double amount)
  {
    if (amount > 0)
      balance += amount;
    else
      cout << "Invalid deposit amount.\n";
    return *this;
  }

  BankAccount &withdraw(double amount)
  {
    if (amount <= 0)
      cout << "Invalid withdrawal amount.\n";
    else if (amount > balance)
      cout << "Insufficient balance in Account #" << accountNumber << endl;
    else
      balance -= amount;
    return *this;
  }

  static void showCounter()
  {
    cout << "\nTotal Accounts Created: " << counter << endl;
  }

  friend ostream &operator<<(ostream &out, const BankAccount &acc)
  {
    out << "\n--- Account Details ---\n";
    out << "Holder Name: " << acc.accountHolder << endl;
    out << "Account Number: " << acc.accountNumber << endl;
    out << "Balance: " << acc.balance << endl;
    return out;
  }

  friend istream &operator>>(istream &in, BankAccount &acc)
  {
    cout << "Enter Account Holder Name: ";
    getline(in, acc.accountHolder);
    cout << "Enter Initial Balance: ";
    in >> acc.balance;
    return in;
  }
};

int BankAccount::counter = 0;
int BankAccount::nextID = 1000;

int main()
{
  BankAccount acc1;
  string name = "Shanab";
  BankAccount acc2("Shanab", 123);

  acc2.deposit(2000).deposit(1500).withdraw(1000);
  cout << acc2;

  acc1.deposit(300).withdraw(100);
  cout << acc1;

  BankAccount acc3;
  // BankAccount acc33(acc3);
  // acc33 = acc3;
  cin >> acc3;
  cout << acc3;

  BankAccount::showCounter();

  BankAccount acc4 = move(acc3);
  cout << "After move:" << acc4;
  cout << acc3;

  return 0;
}
