#include <bits/stdc++.h>

using namespace std;

// LSP states that a derived class should/can be able to act a substitue for a base class at any possible time

// we have defined a abstract cls that enforces withdraw and deposit
class Account
{
public:
    virtual void withdraw(int amt) = 0;
    virtual void deposit(int amt) = 0;
};

// savings account has both withdraw and deposit
class SavingsAccount : public Account
{
private:
    int balance = 0;

public:
    void withdraw(int amt)
    {
        if (this->balance - amt >= 0)
        {
            cout << "Amount with drawed" << endl;
            this->balance -= amt;
            cout << "Current Balance : " << this->balance << endl;
        }
        else
        {
            cout << "Amount is higher than the balance" << endl;
        }
    }
    void deposit(int amt)
    {
        this->balance += amt;

        cout << "Amount of :" << amt << " has been added to the account" << endl;
        cout << "Current balance : " << this->balance << endl;
    }
};

// what if we need another acc called a fixed deposit acc which only supports deposit and no withdraw
class FixedDepositAccount : public Account
{
private:
    int balance = 0;

public:
    // throw a exception to client -> this is one way to handle but it violates LSP, becoz now withdraw does not work , which is must method in the parent class
    void withdraw(int amt)
    {
        throw logic_error("you cant withdraw from a fixed deposit account");
    }
    void deposit(int amt)
    {
        this->balance += amt;

        cout << "Amount of :" << amt << " has been added to the account" << endl;
        cout << "Current balance : " << this->balance << endl;
    }
};

class BankClient
{
private:
    vector<Account *> Accounts;

public:
    BankClient() {}

    void addAccount(Account *acc)
    {
        Accounts.push_back(acc);
    }

    void processTransactions()
    {
        for (Account *acc : Accounts)
        {
            acc->deposit(100);

            try
            {
                acc->withdraw(50);
            }
            catch (const logic_error e)
            {
                cout << e.what() << endl;
            }
        }
    }
};

int main()
{

    Account *sa = new SavingsAccount();
    Account *fda = new FixedDepositAccount();

    BankClient bc;

    bc.addAccount(sa);
    bc.addAccount(fda);

    bc.processTransactions();

    return 0;
}