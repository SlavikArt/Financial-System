#pragma once
#include <fstream>
#include "Report.h"
#include "Account.h"

class Reporter
{
public:
	Reporter();

	Report GenerateDayExpensesReport(Account* account);
	Report GenerateWeekExpensesReport(Account* account);
	Report GenerateMonthExpensesReport(Account* account);

	Report GenerateTopExpenseDayReport(Account* account);
	Report GenerateTopExpenseWeekReport(Account* account);
	Report GenerateTopExpenseMonthReport(Account* account);

	Report GenerateTopCategoryDayReport(Account* account);
	Report GenerateTopCategoryWeekReport(Account* account);
	Report GenerateTopCategoryMonthReport(Account* account);

	bool SaveReportToFile(Report report);
};

