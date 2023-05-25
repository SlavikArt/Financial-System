#pragma once
#include <iostream>
#include <vector>
#include "Expense.h"

class MoneyStorage
{
protected:
	std::string id; // 312578
	std::string name; // Salaries
	std::string typeName; // Visa Gold / Bitcoin
	std::string userName; // Viacheslav
	std::string currency; // USD / BTC
	double balance; // 150000
	std::vector<Expense*> expenses; // expenses
public:
	MoneyStorage();
	// new MoneyStorage("312578", "Salaries", "Visa Gold", "Viacheslav");
	MoneyStorage(std::string id, std::string name, std::string currency, std::string typeName, std::string userName);

	std::string GetId();
	std::string GetName();
	std::string GetTypeName();
	std::string GetUserName();
	std::string GetCurrency();
	double GetBalance();

	std::vector<Expense*> GetAllExpenses();
	std::vector<Expense*> GetExpensesByName(std::string name);
	std::vector<Expense*> GetExpensesByCategory(Category category);
	std::vector<Expense*> GetExpensesByDate(Date date);

	virtual std::string ToString(bool toTable = false) = 0;
	virtual void Input() = 0;

	void Deposit(double amount); // FinanceSystem.StorageByName("Salaries").Deposit(500)
	bool Withdraw(double amount); // FinanceSystem.StorageByName("Salaries").Withdraw(300)
	void AddExpense(Expense* expense);
	void AddNewExpense();

	virtual ~MoneyStorage();
};
