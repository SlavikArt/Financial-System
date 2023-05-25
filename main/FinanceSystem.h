#pragma once
#include <iostream>
#include <vector>
#include <conio.h>
#include <string>
#include "Account.h"
#include "functions.h"
#include "ConsoleTable.h"
#include "Card.h"
#include "Wallet.h"
#include "Report.h"
#include "Reporter.h"

enum OperationType
{
	DEPOSIT,
	WITHDRAW,
};

class FinanceSystem
{
	std::vector<Account*> accounts;
	std::vector<Report> reports;
public:
	FinanceSystem() {}
	FinanceSystem(std::vector<Account*> accounts);

	void CreateNewAccountMenu();

	void AddAccount(Account* account);
	std::vector<Account*> GetAllAccounts();

	void ShowMenu();
	void ShowAccountsMenu();
	void ShowReportsMenu();

	void ShowAccountMenu(int index);
	void ShowReportAccountMenu(int index);

	void DepositMenu(int index);
	void WithdrawMenu(int index);
	void NewExpanseMenu(int index);
	void NewStorageMenu(Storage type, int index);

	void ShowTable(std::string name, 
		std::vector<MoneyStorage*>& storages, Storage type);
	void ShowTable(std::string name, 
		std::vector<MoneyStorage*>& storages, Storage type, int& index);

	~FinanceSystem();
};
