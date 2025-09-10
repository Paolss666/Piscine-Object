#ifndef DIVIDEANDRULE
#define DIVIDEANDRULE

#include <iostream>
#include <vector>

class Bank;

class Account
{
private:
    int _id;
    int _value;

    friend class Bank; // only this class can modify accounts;

    Account(int id);

public:
    const int &getId() const;
    const int &getValue() const;

    friend std::ostream &operator<<(std::ostream &p_os, const Account &p_account);
};

class Bank
{
private:
    int _liquidity;
    std::vector<Account *> _clientAccounts;
    int _nextId;

    Account *findAccount(int id);
    bool IsIdExists(int id);

public:
    const int &getLiquidity() const;
    const std::vector<Account *> &getListAccounts() const;

    void setLiquidity(const int p_liquidity);

    bool deleteAccount(int p_id);
    bool deposit(int accountId, int amount);
    bool withdraw(int accoutId, int amout);
    bool giveLoan(int accoutId, int amout);
    bool transfer(int fromAccountId, int toAccountId, int amount);

    Bank();
    ~Bank();

    Account *createAccount();

    friend std::ostream &operator<<(std::ostream &p_os, const Bank &p_bank);
};

#endif