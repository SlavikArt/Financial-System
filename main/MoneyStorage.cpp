#include "MoneyStorage.h"

MoneyStorage::MoneyStorage()
	: id(""), name(""),
	currency(""), typeName(""),
	userName(""), balance(0), 
	expenses() {}

MoneyStorage::MoneyStorage(std::string id, std::string name, 
	std::string currency, std::string typeName, std::string userName) 
	: id(id), name(name), currency(currency), typeName(typeName), 
	userName(userName), balance(0), expenses() {}

std::string MoneyStorage::GetId()
{
	return this->id;
}

std::string MoneyStorage::GetName()
{
	return this->name;
}

std::string MoneyStorage::GetTypeName()
{
	return this->typeName;
}

std::string MoneyStorage::GetUserName()
{
	return this->userName;
}

std::string MoneyStorage::GetCurrency()
{
	return this->currency;
}

double MoneyStorage::GetBalance()
{
	return this->balance;
}

std::vector<Expense*> MoneyStorage::GetAllExpenses()
{
	return expenses;
}

std::vector<Expense*> MoneyStorage::GetExpensesByName(std::string name)
{
	std::vector<Expense*> tmp;

	for (auto& expense : expenses)
		if (expense->GetName() == name)
			tmp.push_back(expense);
	return tmp;
}

std::vector<Expense*> MoneyStorage::GetExpensesByCategory(Category category)
{
	std::vector<Expense*> tmp;

	for (auto& expense : expenses)
		if (expense->GetCategory() == category)
			tmp.push_back(expense);
	return tmp;
}

std::vector<Expense*> MoneyStorage::GetExpensesByDate(Date date)
{
	std::vector<Expense*> tmp;

	for (auto& expense : expenses)
		if (expense->GetDate() == date)
			tmp.push_back(expense);
	return tmp;
}

void MoneyStorage::Deposit(double amount)
{
	this->balance += amount;
	this->expenses.push_back(
		new Expense(
			"Deposit",
			Category(Transaction, 0),
			Date(0),
			Time(0),
			amount,
			this->balance
		)
	);
}

bool MoneyStorage::Withdraw(double amount)
{
	if (amount < 0) amount *= -1;

	if (this->balance - amount >= 0)
	{
		this->balance -= amount;
		this->expenses.push_back(
			new Expense(
				"Withdraw",
				Category(Transaction, 0),
				Date(0),
				Time(0),
				-amount,
				this->balance
			)
		);
		return true;
	}
	else
		return false;
}

void MoneyStorage::AddExpense(Expense* expense)
{
	this->expenses.push_back(expense);
}

void MoneyStorage::AddNewExpense()
{
	Expense* expense = new Expense();
	expense->Input(this->balance);

	AddExpense(expense);
}

MoneyStorage::~MoneyStorage()
{
	for (auto& expense : expenses)
	{
		delete expense;
	}
}
