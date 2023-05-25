#include "Card.h"

Card::Card(): MoneyStorage(),
	isCredit(false), creditLimit(0), maxCreditLimit(0) {}

Card::Card(std::string id, std::string name, 
	std::string currency, std::string typeName, 
	std::string userName, double maxCreditLimit) 
	: MoneyStorage(id, name, currency, typeName, userName)
{
	this->maxCreditLimit = maxCreditLimit;

	if (maxCreditLimit > 0)
	{
		isCredit = true;
		creditLimit = maxCreditLimit;
	}
	else
	{
		isCredit = false;
		creditLimit = 0;
	}
}

bool Card::IsCredit()
{
	return this->isCredit;
}

double Card::GetCreditLimit()
{
	return this->creditLimit;
}

std::string Card::ToString(bool toTable)
{
	std::stringstream s;

	s << "Card:\n"
		<< "Name: " << name << "\n"
		<< "Type: " << typeName << "\n"
		<< "Owner: " << userName << "\n"
		<< "Currency: " << currency << "\n"
		<< "Balance: " << balance << "\n"
		<< "Expenses:\n";

	for (auto& expense : expenses)
		if (!toTable)
			s << expense->ToString();
		else
			s << expense->ToString(true);
	return s.str();
}

void Card::Input()
{
	std::cout << "New Card:\n";

	std::cout << "Card Name: ";
	/*std::cin.ignore();*/
	std::getline(std::cin, name);

	std::cout << "ID: ";
	//std::cin.ignore();
	std::getline(std::cin, id);

	std::cout << "Type: ";
	//std::cin.ignore();
	std::getline(std::cin, typeName);

	std::cout << "Owner: ";
	//std::cin.ignore();
	std::getline(std::cin, userName);

	std::cout << "Currency: ";
	//std::cin.ignore();
	std::getline(std::cin, currency);

	std::cout << "Max Credit Limit (0): ";
	//std::cin.ignore();
	std::cin >> maxCreditLimit;

	if (maxCreditLimit > 0)
	{
		isCredit = true;
		creditLimit = maxCreditLimit;
	}
	else
	{
		isCredit = false;
		creditLimit = 0;
	}
}
