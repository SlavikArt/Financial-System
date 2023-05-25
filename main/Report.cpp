#include "Report.h"

Report::Report() 
	: name(""), accountName(""), expenses() {}

Report::Report(std::string name, std::string accountName, std::vector<Expense> expenses) 
    : name(name), accountName(accountName), expenses(expenses) {}

std::string Report::GetName()
{
    return name;
}

std::string Report::GetAccountName()
{
    return accountName;
}

std::string Report::ToString()
{
    std::stringstream s;
    s << "Report Name: " << name << "\n"
        << "Account Name: " << accountName << "\n"
        << "Expenses: " << "\n";

    ConsoleTable table{ "Name", "Payment", "Date", "Time", "Category", "Balance After" };
    for (auto& expense : expenses)
    {
        table +=
        {
            expense.GetName(),
            std::to_string(expense.GetPaymentAmount()),
            expense.GetDate().ToString(),
            expense.GetTime().ToString(),
            CategoryTypeToString(expense.GetCategory().GetType()),
            std::to_string(expense.GetBalanceAfter())
        };
    }
    s << table;
    return s.str();
}
