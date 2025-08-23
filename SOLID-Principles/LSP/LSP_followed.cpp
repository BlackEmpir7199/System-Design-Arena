#include <bits/stdc++.h>

using namespace std;

// LSP states that a derived class should/can be able to act a substitue for a base class at any possible time

// we have defined a abstract cls that enforces deposit + highest in the hierarcy + most simple should be defined as the high lvl class from which derivations happen
class DepositAccount
{
public:
    virtual void deposit(int amt) = 0;
};

// we derive withdraw acc from deposit acc class thus maintaining lsp and enabling oc
class WithdrawAccount : DepositAccount
{
public:
    virtual void deposit(int amt) = 0;
    virtual void withdraw(int amt) = 0;
};

// savings account extends withdrawaccount
class SavingsAccount : public WithdrawAccount
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

// now LSP is not broke here becoz fixedDepositAccount can be clearly used as a substitue for deposit Account
class FixedDepositAccount : public DepositAccount
{
private:
    int balance = 0;

public:
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
    vector<DepositAccount *> depositAccounts;
    vector<WithdrawAccount *> WithdrawAccounts;

public:
    BankClient() {}

    void addDepositAccount(DepositAccount *acc)
    {
        depositAccounts.push_back(acc);
    }

    void addWithdrawAccounts(WithdrawAccount *acc)
    {
        WithdrawAccounts.push_back(acc);
    }

    // writing separated logic for deposit and withraw account , clean codes baby
    void processTransactions()
    {
        for (DepositAccount *acc : depositAccounts)
        {
            acc->deposit(100);
        }

        for (WithdrawAccount *acc : WithdrawAccounts)
        {
            acc->deposit(100);
            acc->withdraw(50);
        }
    }
};

int main()
{

    BankClient bc;

    WithdrawAccount *sa = new SavingsAccount();
    DepositAccount *fda = new FixedDepositAccount();

    bc.addWithdrawAccounts(sa);
    bc.addDepositAccount(fda);

    bc.processTransactions();

    return 0;
}