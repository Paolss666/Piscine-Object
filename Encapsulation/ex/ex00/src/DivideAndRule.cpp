#include "../incl/DivideAndRule.hpp"

Account::Account(int id) : _id(id), _value(0) {}

const int &Account::getId() const
{
	return _id;
}

const int &Account::getValue() const
{
	return _value;
}

std::ostream &operator<<(std::ostream &p_os, const Account &p_account)
{
	p_os << "[" << p_account._id << "] - [" << p_account._value << "]";
	return (p_os);
}

Bank::Bank() : _liquidity(0), _clientAccounts(0), _nextId(0) {}

Bank::~Bank()
{
	for (std::vector<Account *>::iterator it = _clientAccounts.begin();
		 it != _clientAccounts.end(); ++it)
	{
		delete (*it);
	}
}

Account *Bank::findAccount(int id)
{
	for (std::vector<Account *>::iterator it = _clientAccounts.begin();
		 it != _clientAccounts.end(); ++it)
	{
		if ((*it)->getId() == id)
			return (*it);
	}
	return NULL;
}

bool Bank::IsIdExists(int id)
{
	for (std::vector<Account *>::iterator it = _clientAccounts.begin();
		 it != _clientAccounts.end(); ++it)
	{
		if ((*it)->_id == id)
			return true;
	}
	return false;
}

const int &Bank::getLiquidity() const
{
	return _liquidity;
}

const std::vector<Account *> &Bank::getListAccounts() const
{
	return _clientAccounts;
}

void Bank::setLiquidity(const int p_liquidity)
{
	this->_liquidity = p_liquidity;
}

Account *Bank::createAccount()
{
	while (IsIdExists(_nextId))
		_nextId++;

	Account *newAccount = new Account(_nextId);
	_clientAccounts.push_back(newAccount);
	_nextId++;
	return newAccount;
}

bool Bank::deleteAccount(int p_id)
{
	for (std::vector<Account *>::iterator it = _clientAccounts.begin();
		 it != _clientAccounts.end(); ++it)
	{
		if ((*it)->_id == p_id)
		{
			delete (*it);
			_clientAccounts.erase(it);
			return true;
		}
	}
	return false;
}

bool Bank::deposit(int accountId, int amount)
{
	if (amount <= 0)
		return false;

	Account *accountFound = findAccount(accountId);

	if (accountFound == NULL)
		return false;

	int bankFee = amount * 5 / 100;
	int clientAmount = amount - bankFee;

	accountFound->_value += clientAmount;
	_liquidity += bankFee;

	return true;
}

bool Bank::withdraw(int accountId, int amount)
{
	if (amount <= 0) // bank dont have liq
		return false;

	Account *accountFound = findAccount(accountId);
	if (accountFound == NULL || accountFound->_value < amount)
		return false;

	accountFound->_value -= amount;
	return true;
}

bool Bank::giveLoan(int accountId, int amount)
{
	if (amount <= 0 || _liquidity < amount) // bank dont have liq
		return false;

	Account *accountFound = findAccount(accountId);
	if (accountFound == NULL)
		return false;

	accountFound->_value += amount;
	_liquidity -= amount;

	return true;
}

bool Bank::transfer(int fromAccountId, int toAccountId, int amount)
{
	if (amount <= 0)
		return false;

	Account *fromAccount = findAccount(fromAccountId);
	Account *toAccount = findAccount(toAccountId);
	if (!fromAccount || !toAccount)
		return false;

	int bankFee = amount * 5 / 100;

	int totalDeduction = amount + bankFee;

	if (fromAccount->_value < totalDeduction)
		return false;

	fromAccount->_value -= totalDeduction;
	toAccount->_value += amount;

	_liquidity += bankFee;

	return true;
}

std::ostream &operator<<(std::ostream &p_os, const Bank &p_bank)
{
	p_os << "Bank informations : " << std::endl;
	p_os << "Liquidity : " << p_bank._liquidity << std::endl;
	for (std::vector<Account *>::const_iterator it = p_bank._clientAccounts.begin();
		 it != p_bank._clientAccounts.end(); ++it)
	{
		p_os << **it << std::endl;
	}
	return (p_os);
}

// struct Account
// {
// 	int _id;
// 	int _value;

// 	Account() : _id(-1),
// 				_value(0)
// 	{
// 	}

// 	friend std::ostream &operator<<(std::ostream &p_os, const Account &p_account)
// 	{
// 		p_os << "[" << p_account._id << "] - [" << p_account._value << "]";
// 		return (p_os);
// 	}
// };

// struct Bank
// {
// 	int liquidity;
// 	std::vector<Account *> clientAccounts;

// 	Bank() : liquidity(0)
// 	{
// 	}

// 	friend std::ostream &operator<<(std::ostream &p_os, const Bank &p_bank)
// 	{
// 		p_os << "Bank informations : " << std::endl;
// 		p_os << "Liquidity : " << p_bank.liquidity << std::endl;

// 		for (std::vector<Account *>::iterator it = p_bank.clientAccounts.begin();
// 			 it != p_bank.clientAccounts.end(); ++it)
// 		{
// 			p_os << **it << std::endl;
// 		}
// 		return (p_os);
// 	}
// };
