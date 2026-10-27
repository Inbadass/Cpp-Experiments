#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

// Base custom exception class
class BankException : public exception
{
protected:
    string message;
public:
    BankException(string msg) { message = msg; }

    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

class InsufficientFundsException : public BankException
{
public:
    InsufficientFundsException()
        : BankException("Error: Insufficient balance for withdrawal.") {}
};

class InvalidAmountException : public BankException
{
public:
    InvalidAmountException()
        : BankException("Error: Amount must be greater than zero.") {}
};

class BankAccount
{
private:
    string name;
    double balance;
    int transactions;   // counts only successful operations

public:
    BankAccount(string n, double b)
    {
        name = n;
        balance = b;
        transactions = 0;
    }

    void deposit(double amount)
    {
        if (amount <= 0)
            throw InvalidAmountException();
        balance += amount;
        transactions++;
    }

    void withdraw(double amount)
    {
        // Validate first before modifying the state
        if (amount <= 0)
            throw InvalidAmountException();
        if (amount > balance)
            throw InsufficientFundsException();

        // State changes only after all checks succeed
        balance -= amount;
        transactions++;
    }

    double getBalance() const { return balance; }

    void display() const
    {
        cout << "Account Holder: " << name << endl;
        cout << "Balance: Rs. " << balance << endl;
        cout << "Successful Transactions: " << transactions << endl;
    }
};

// Runs one operation and reports the result
void perform(BankAccount &acc, char type, double amount)
{
    try
    {
        if (type == 'D')
        {
            cout << "Depositing Rs. " << amount << "..." << endl;
            acc.deposit(amount);
        }
        else
        {
            cout << "Withdrawing Rs. " << amount << "..." << endl;
            acc.withdraw(amount);
        }
        cout << "Success. Balance: Rs. " << acc.getBalance() << endl;
    }
    catch (const InsufficientFundsException &e)
    {
        cout << e.what() << endl;
        cout << "Balance unchanged: Rs. " << acc.getBalance() << endl;
    }
    catch (const InvalidAmountException &e)
    {
        cout << e.what() << endl;
        cout << "Balance unchanged: Rs. " << acc.getBalance() << endl;
    }
    catch (const BankException &e)
    {
        cout << "Bank Exception: " << e.what() << endl;
    }
    catch (const exception &e)
    {
        cout << "General Exception: " << e.what() << endl;
    }
    cout << endl;
}

int main()
{
    BankAccount account("Arun", 5000);

    cout << "Initial Account Details:" << endl;
    account.display();
    cout << endl;

    perform(account, 'D', 1000);
    perform(account, 'W', 2000);
    perform(account, 'D', -500);     // invalid amount
    perform(account, 'W', 10000);    // insufficient funds

    cout << "Final Account Details:" << endl;
    account.display();

    cout << "\nThe strong exception guarantee means: if an operation fails,"
         << "\nthe account remains exactly as it was before the operation." << endl;
    return 0;
}
