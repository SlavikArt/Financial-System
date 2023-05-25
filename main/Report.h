#pragma once
#include <iostream>
#include "functions.h"
#include "Expense.h"

class Report
{
	std::string name; // 25-05-2023
	std::string accountName; // Viacheslav
	std::vector<Expense> expenses; // expenses in report
public:
	Report();
	Report(std::string name, std::string accountName, std::vector<Expense> expenses);
	
	std::string GetName();
	std::string GetAccountName();

	std::string ToString();
};

