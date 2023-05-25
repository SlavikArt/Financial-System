#include "Expense.h"

Expense::Expense() : name(""), category(Category()),date(Date(0)),
	time(Time(0)), paymentAmount(0), balanceAfter(0) {}

Expense::Expense(std::string name, Category category, Date date, 
	Time time, double paymentAmount, double balanceAfter) 
	: name(name), category(category), date(date), time(time), 
	paymentAmount(paymentAmount), balanceAfter(balanceAfter) {}

std::string Expense::GetName()
{
	return this->name;
}

Category Expense::GetCategory()
{
	return this->category;
}

Date Expense::GetDate()
{
	return this->date;
}

Time Expense::GetTime()
{
	return this->time;
}

double Expense::GetPaymentAmount() const
{
	return this->paymentAmount;
}

double Expense::GetBalanceAfter()
{
	return this->balanceAfter;
}

void Expense::Input(double& currentBalance)
{
	std::cout << "New Expense:\n";
	std::cout << "Name: ";

	std::cin.ignore();
	std::getline(std::cin, this->name);
	
	std::cout << "Choose the Category:\n";
	for (int i = None + 1; i <= Other; i++)
	{
		std::string categoryStr = CategoryTypeToString(static_cast<CategoryType>(i));
		std::cout << i << " - " << categoryStr << "\n";
	}
	int typeChoice = 0;
	
	std::cout << "Category: ";
	std::cin >> typeChoice;
	this->category = Category(static_cast<CategoryType>(typeChoice));

	this->date = Date(0);
	this->time = Time(0);
	do
	{
		std::cout << "Enter the payment amount: ";
		std::cin >> this->paymentAmount;
		if (currentBalance - paymentAmount >= 0)
		{
			currentBalance -= paymentAmount;
			balanceAfter = currentBalance;

			std::cout << "Success, your balance after is "
				<< balanceAfter << "\n";

			char tmp;
			std::cout << "Enter any char to continue\n>>> ";
			std::cin >> tmp;
			break;
		}
		else
			std::cout << "Not enough money on the balance, try again\n";
	} while (currentBalance - paymentAmount < 0);
	
}

std::string Expense::ToString(bool toTable)
{
	std::stringstream s;
	std::string categoryType = CategoryTypeToString(category.GetType());

	if (!toTable)
	{	
		s << "Expense:\n"
			<< "Name: " << name << "\n"
			<< "Category: " << categoryType << "\n"
			<< "Date: " << date << "\n"
			<< "Time: " << time << "\n"
			<< "Payment: " << paymentAmount << "\n"
			<< balanceAfter << "\n";
		return s.str();
	}
	else
	{
		ConsoleTable table{ "Name", "Payment", "Date", "Time", "Category", "Balance After" };
		table +=
		{
			name,
			std::to_string(paymentAmount),
			date.ToString(),
			time.ToString(),
			categoryType,
			std::to_string(balanceAfter)
		};
		s << table;
		return s.str();
	}
	
	
}

bool Expense::operator<(const Expense& other) const
{
	return this->paymentAmount < other.paymentAmount;
}
