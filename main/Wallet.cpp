#include "Wallet.h"

Wallet::Wallet() : MoneyStorage(),
	isCrypto(false), networkName("") {}

Wallet::Wallet(std::string id, std::string name,
    std::string currency, std::string typeName,
    std::string userName, bool isCrypto, std::string networkName)
    : MoneyStorage(id, name, currency, typeName, userName),
    isCrypto(isCrypto), networkName(networkName) {}

std::string Wallet::GetNetwork()
{
    return this->networkName;
}

bool Wallet::IsCrypto()
{
    return isCrypto;
}

std::string Wallet::ToString(bool toTable)
{
    std::stringstream s;

    s << "Wallet:\n"
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

void Wallet::Input()
{
	std::cout << "New Wallet:\n";

	std::cout << "Wallet Name: ";
	std::cin.ignore();
	std::getline(std::cin, name);

	std::cout << "ID: ";
	std::cin.ignore();
	std::getline(std::cin, id);

	std::cout << "Type: ";
	std::cin.ignore();
	std::getline(std::cin, typeName);

	std::cout << "Owner: ";
	std::cin.ignore();
	std::getline(std::cin, userName);

	std::cout << "Currency: ";
	std::cin.ignore();
	std::getline(std::cin, currency);

	std::cout << "Network Name: ";
	std::cin.ignore();
	std::getline(std::cin, networkName);

	int tmp = 0;
	std::cout << "Is Crypto? (1 or 0): ";
	std::cin.ignore();
	std::cin >> tmp;
	isCrypto = tmp > 0 ? true : false;
}
