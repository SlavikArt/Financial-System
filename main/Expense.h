#pragma once
#include <iostream>
#include <sstream>
#include "ConsoleTable.h"
#include "Category.h"
#include "Date.h"
#include "Time.h"

class Expense
{
	std::string name; // Sushi Master
	Category category; // Cafes and Restaurants // category -> name, cashbackPercentage
	Date date; // 15.05.2023
	Time time; // 16:40
	double paymentAmount; // 500
	double balanceAfter; // 1000
public:
	Expense();
	Expense(std::string name, Category category, Date date, Time time, double paymentAmount, double balanceAfter);
	
	std::string GetName();
	Category GetCategory();
	Date GetDate();
	Time GetTime();
	double GetPaymentAmount() const;
	double GetBalanceAfter();

	void Input(double& currentBalance);
	std::string ToString(bool toTable = false);

	bool operator<(const Expense& other) const;
};
