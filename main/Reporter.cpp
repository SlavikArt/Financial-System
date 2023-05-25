#include "Reporter.h"

Reporter::Reporter() {}

Report Reporter::GenerateDayExpensesReport(Account* account)
{
	Date todayDate = Date(0);
	std::vector<Expense> reportExpenses;

	for (auto& storage : account->GetAllStorages())
		for (auto& expense : storage->GetExpensesByDate(todayDate))
			reportExpenses.push_back(*expense);
	return Report(todayDate.ToString() + "_" + Time(0).ToString(), account->GetName(), reportExpenses);
}

Report Reporter::GenerateWeekExpensesReport(Account* account)
{
	Date todayDate = Date(0); // 25
	Date weekStart = todayDate - 7; // 18

	std::vector<Expense> reportExpenses;

	for (Date d = todayDate; d != weekStart - 1; d = d - 1)
	{
		for (auto& storage : account->GetAllStorages())
			for (auto& expense : storage->GetExpensesByDate(d))
				reportExpenses.push_back(*expense);
	}
	return Report(todayDate.ToString() + "_" + Time(0).ToString(), account->GetName(), reportExpenses);
}

Report Reporter::GenerateMonthExpensesReport(Account* account)
{
	Date todayDate = Date(0); // 25
	Date weekStart = todayDate - 31; // 18

	std::vector<Expense> reportExpenses;

	for (Date d = todayDate; d != weekStart - 1; d = d - 1)
	{
		for (auto& storage : account->GetAllStorages())
			for (auto& expense : storage->GetExpensesByDate(d))
				reportExpenses.push_back(*expense);
	}
	return Report(todayDate.ToString() + "_" + Time(0).ToString(), account->GetName(), reportExpenses);
}

Report Reporter::GenerateTopExpenseDayReport(Account* account)
{
	Date todayDate = Date(0);

	std::vector<Expense> reportExpenses;

	std::set<Expense> top;
	for (auto& storage : account->GetAllStorages())
	{
		for (auto& expense : storage->GetExpensesByDate(todayDate))
		{
			top.insert(*expense);
		}
	}
	auto it = top.rbegin();
	for (int i = 0; i < 3 && it != top.rend(); i++, it++)
	{
		reportExpenses.push_back(*it);
	}
	return Report(todayDate.ToString() + "_" + Time(0).ToString(), account->GetName(), reportExpenses);
}

Report Reporter::GenerateTopExpenseWeekReport(Account* account)
{
	Date todayDate = Date(0); // 25
	Date weekStart = todayDate - 7; // 18

	std::vector<Expense> reportExpenses;

	std::set<Expense> top;
	for (Date d = todayDate; d != weekStart - 1; d = d - 1)
	{
		for (auto& storage : account->GetAllStorages())
		{
			for (auto& expense : storage->GetExpensesByDate(d))
			{
				top.insert(*expense);
			}
		}			
	}
	auto it = top.rbegin();
	for (int i = 0; i < 3 && it != top.rend(); i++, it++)
	{
		reportExpenses.push_back(*it);
	}
	return Report(todayDate.ToString() + "_" + Time(0).ToString(), account->GetName(), reportExpenses);
}

Report Reporter::GenerateTopExpenseMonthReport(Account* account)
{
	Date todayDate = Date(0); // 25
	Date weekStart = todayDate - 31; // 18

	std::vector<Expense> reportExpenses;

	std::set<Expense> top;
	for (Date d = todayDate; d != weekStart - 1; d = d - 1)
	{
		for (auto& storage : account->GetAllStorages())
		{
			for (auto& expense : storage->GetExpensesByDate(d))
			{
				top.insert(*expense);
			}
		}
	}
	auto it = top.rbegin();
	for (int i = 0; i < 3 && it != top.rend(); i++, it++)
	{
		reportExpenses.push_back(*it);
	}
	return Report(todayDate.ToString() + "_" + Time(0).ToString(), account->GetName(), reportExpenses);
}

struct CompareCatTotal
{
	bool operator()(const std::pair<CategoryType, double>& a,
		const std::pair<CategoryType, double>& b) const
	{
		return a.second > b.second;
	}
};

struct CompareExpensePaymentAmount
{
	bool operator()(const Expense& a, const Expense& b) const
	{
		return a.GetPaymentAmount() > b.GetPaymentAmount();
	}
};

Report Reporter::GenerateTopCategoryDayReport(Account* account)
{
	Date todayDate = Date(0);

	std::vector<Expense> reportExpenses;

	std::map<CategoryType, std::vector<Expense>> cat;
	for (auto& storage : account->GetAllStorages())
	{
		for (auto& expense : storage->GetExpensesByDate(todayDate))
		{
			CategoryType type = expense->GetCategory().GetType();
			switch (type)
			{
			case CafesAndRestaurants:
				cat[type].push_back(*expense);
				break;
			case Grocery:
				cat[type].push_back(*expense);
				break;
			case Transaction:
				cat[type].push_back(*expense);
				break;
			case Other:
				cat[type].push_back(*expense);
				break;
			default:
				break;
			}
		}
	}
	
	std::map<CategoryType, double> catTotal;
	for (auto it = cat.begin(); it != cat.end(); it++)
	{
		CategoryType type = it->first;
		std::vector<Expense>& expenses = it->second;

		double total = 0;
		for (auto& expense : expenses)
			total += expense.GetPaymentAmount();
		catTotal[type] = total;
	}

	std::vector<std::pair<CategoryType, double>> sortedCat(catTotal.begin(), catTotal.end());
	std::sort(sortedCat.begin(), sortedCat.end(), CompareCatTotal());

	for (int i = 0; i < 3 && i < sortedCat.size(); i++)
	{
		CategoryType type = sortedCat[i].first;
		std::vector<Expense>& expenses = cat[type];
		std::sort(expenses.begin(), expenses.end(), CompareExpensePaymentAmount());

		if (!expenses.empty())
			reportExpenses.push_back(expenses[0]);
	}
	return Report(todayDate.ToString() + "_" + Time(0).ToString(), account->GetName(), reportExpenses);
}


Report Reporter::GenerateTopCategoryWeekReport(Account* account)
{
	Date todayDate = Date(0); // 25
	Date weekStart = todayDate - 7; // 18

	std::vector<Expense> reportExpenses;

	std::map<CategoryType, std::vector<Expense>> cat;
	for (Date d = todayDate; d != weekStart - 1; d = d - 1)
	{
		for (auto& storage : account->GetAllStorages())
		{
			for (auto& expense : storage->GetExpensesByDate(d))
			{
				CategoryType type = expense->GetCategory().GetType();
				switch (type)
				{
				case CafesAndRestaurants:
					cat[type].push_back(*expense);
					break;
				case Grocery:
					cat[type].push_back(*expense);
					break;
				case Transaction:
					cat[type].push_back(*expense);
					break;
				case Other:
					cat[type].push_back(*expense);
					break;
				default:
					break;
				}
			}
		}
	}
	
	std::map<CategoryType, double> catTotal;
	for (auto it = cat.begin(); it != cat.end(); it++)
	{
		CategoryType type = it->first;
		std::vector<Expense>& expenses = it->second;

		double total = 0;
		for (auto& expense : expenses)
			total += expense.GetPaymentAmount();
		catTotal[type] = total;
	}

	std::vector<std::pair<CategoryType, double>> sortedCat(catTotal.begin(), catTotal.end());
	std::sort(sortedCat.begin(), sortedCat.end(), CompareCatTotal());

	for (int i = 0; i < 3 && i < sortedCat.size(); i++)
	{
		CategoryType type = sortedCat[i].first;
		std::vector<Expense>& expenses = cat[type];
		std::sort(expenses.begin(), expenses.end(), CompareExpensePaymentAmount());

		if (!expenses.empty())
			reportExpenses.push_back(expenses[0]);
	}
	return Report(todayDate.ToString() + "_" + Time(0).ToString(), account->GetName(), reportExpenses);
}

Report Reporter::GenerateTopCategoryMonthReport(Account* account)
{
	Date todayDate = Date(0); // 25
	Date weekStart = todayDate - 31; // 18

	std::vector<Expense> reportExpenses;

	std::map<CategoryType, std::vector<Expense>> cat;
	for (Date d = todayDate; d != weekStart - 1; d = d - 1)
	{
		for (auto& storage : account->GetAllStorages())
		{
			for (auto& expense : storage->GetExpensesByDate(d))
			{
				CategoryType type = expense->GetCategory().GetType();
				switch (type)
				{
				case CafesAndRestaurants:
					cat[type].push_back(*expense);
					break;
				case Grocery:
					cat[type].push_back(*expense);
					break;
				case Transaction:
					cat[type].push_back(*expense);
					break;
				case Other:
					cat[type].push_back(*expense);
					break;
				default:
					break;
				}
			}
		}
	}

	std::map<CategoryType, double> catTotal;
	for (auto it = cat.begin(); it != cat.end(); it++)
	{
		CategoryType type = it->first;
		std::vector<Expense>& expenses = it->second;

		double total = 0;
		for (auto& expense : expenses)
			total += expense.GetPaymentAmount();
		catTotal[type] = total;
	}

	std::vector<std::pair<CategoryType, double>> sortedCat(catTotal.begin(), catTotal.end());
	std::sort(sortedCat.begin(), sortedCat.end(), CompareCatTotal());

	for (int i = 0; i < 3 && i < sortedCat.size(); i++)
	{
		CategoryType type = sortedCat[i].first;
		std::vector<Expense>& expenses = cat[type];
		std::sort(expenses.begin(), expenses.end(), CompareExpensePaymentAmount());

		if (!expenses.empty())
			reportExpenses.push_back(expenses[0]);
	}
	return Report(todayDate.ToString() + "_" + Time(0).ToString(), account->GetName(), reportExpenses);
}

bool Reporter::SaveReportToFile(Report report)
{
	std::string filename = report.GetName() + ".txt";

	std::ofstream file(filename);
	if (!file.is_open())
		return false;

	file << report.ToString();
	file.close();

	return true;
}
