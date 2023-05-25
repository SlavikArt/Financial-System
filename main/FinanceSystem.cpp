#include "FinanceSystem.h"

FinanceSystem::FinanceSystem(std::vector<Account*> accounts)
{
	this->accounts = accounts;
}

void FinanceSystem::CreateNewAccountMenu()
{
	/*
	* Let's create new account:
	* Account name: Jake
	*/
	system("cls");

	std::cout << "Let's create new account:\n";
	std::cout << "Account name: ";

	std::cin.ignore();
	
	std::string acName;
	std::getline(std::cin, acName);

	this->AddAccount(new Account(acName));
}

void FinanceSystem::AddAccount(Account* account)
{
	this->accounts.push_back(account);
}

std::vector<Account*> FinanceSystem::GetAllAccounts()
{
	return this->accounts;
}

void FinanceSystem::ShowMenu()
{
	/*
	* Financial System
	* 1. Accounts
	* 2. Reports
	*/
	char ch;
	do
	{
		system("cls");
		
		std::cout << "Financial System\n";
		std::cout << "1. Accounts\n";
		std::cout << "2. Reports\n";
		std::cout << "E. Exit\n\n";

		std::cout << ">>> ";
		std::cin >> ch;

		switch (ch)
		{
		case '1':
			ShowAccountsMenu();
			break;
		case '2':
			ShowReportsMenu();
			break;
		default:
			break;
		}
	} while (ch != 'e' && ch != 'E');
}

void FinanceSystem::ShowAccountsMenu()
{
	/*
	* Accounts:
	* 0. Create new
	* 1. User 1
	* 2. Viacheslav
	* E. Back
	*/
	char ch;
	do
	{
		system("cls");

		std::cout << "Accounts\n";
		std::cout << "0. Create new\n";
		for (int i = 0; i < accounts.size(); i++) // ShowAllAccounts?
		{
			std::cout << i + 1 << ". " 
				<< accounts[i]->GetName() << "\n";
		}
		std::cout << "E. Back\n\n";

		std::cout << ">>> ";
		std::cin >> ch;

		if (ch != 'e' && ch != 'E')
		{
			int chInt = ch - '0';

			if (chInt > 0 && chInt <= accounts.size())
				ShowAccountMenu(chInt - 1);
			else if (chInt == 0)
				CreateNewAccountMenu();
		}
	} while (ch != 'e' && ch != 'E');
}

void FinanceSystem::ShowReportsMenu()
{
	char ch;
	do
	{
		system("cls");

		Reporter reporter;

		std::cout << "Reports/Account\n";
		std::cout << "0. Back\n";
		for (int i = 0; i < accounts.size(); i++) // ShowAllAccounts?
		{
			std::cout << i + 1 << ". "
				<< accounts[i]->GetName() << "\n";
		}
		std::cout << "\n";

		std::cout << ">>> ";
		std::cin >> ch;

		if (ch != 'e' && ch != 'E')
		{
			int chInt = ch - '0';

			if (chInt > 0 && chInt <= accounts.size())
				ShowReportAccountMenu(chInt - 1);
			else if (chInt == 0)
				break;
		}
	} while (ch != 'e' && ch != 'E');
}

void FinanceSystem::ShowAccountMenu(int index)
{
	/*
	* Viacheslav's account
	* Viacheslav/Cards
	*  *table*
	* Viacheslav/Wallets
	*  *table*
	* 1. Deposit, 2. Withdraw, 3. New Expese
	*/
	char ch;
	do
	{
		system("cls");

		Account* account = accounts[index];

		std::string accountName = account->GetName();

		std::vector<MoneyStorage*> cardsArray = account->GetAllStoragesWithType(CARD);
		std::vector<MoneyStorage*> walletsArray = account->GetAllStoragesWithType(WALLET);

		std::cout << "Accaunts/" << accountName << "\n\n";
		
		ShowTable(accountName, cardsArray, CARD);
		ShowTable(accountName, walletsArray, WALLET);

		std::cout << "1. Deposit\n";
		std::cout << "2. Withdraw\n";
		std::cout << "3. New Expense\n";
		std::cout << "4. New Card\n";
		std::cout << "5. New Wallet\n";

		std::cout << ">>> ";
		std::cin >> ch;

		switch (ch)
		{
		case '1':
			DepositMenu(index);
			break;
		case '2':
			WithdrawMenu(index);
			break;
		case '3':
			NewExpanseMenu(index);
			break;
		case '4':
			NewStorageMenu(CARD, index);
			break;
		case '5':
			NewStorageMenu(WALLET, index);
			break;
		default:
			break;
		}
	} while (ch != 'e' && ch != 'E');
}

void FinanceSystem::ShowReportAccountMenu(int index)
{
	int ch;
	do
	{
		system("cls");

		Reporter reporter;

		Account* account = accounts[index];

		Report dayReport = reporter.GenerateDayExpensesReport(account);
		Report weekReport = reporter.GenerateWeekExpensesReport(account);
		Report monthReport = reporter.GenerateMonthExpensesReport(account);

		Report dayTopReport = reporter.GenerateTopExpenseDayReport(account);
		Report weekTopReport = reporter.GenerateTopExpenseWeekReport(account);
		Report monthTopReport = reporter.GenerateTopExpenseMonthReport(account);

		Report dayTopCategoryReport = reporter.GenerateTopCategoryDayReport(account);
		Report weekTopCategoryReport = reporter.GenerateTopCategoryWeekReport(account);
		Report monthTopCategoryReport = reporter.GenerateTopCategoryMonthReport(account);

		std::string accountName = account->GetName();

		std::vector<MoneyStorage*> cardsArray = account->GetAllStoragesWithType(CARD);
		std::vector<MoneyStorage*> walletsArray = account->GetAllStoragesWithType(WALLET);

		std::cout << "Reports/" << accountName << "\n\n";

		std::cout << "Choose the type of a Report (0. Back):\n";

		std::cout << "1 - Day Expense Report\n"
			<< "2 - Week Expense Report\n"
			<< "3 - Month Expense Report\n"
			<< "4 - Day Top Report\n"
			<< "5 - Week Top Report\n"
			<< "6 - Month Top Report\n"
			<< "7 - Day Top Category Report\n"
			<< "8 - Week Top Category Report\n"
			<< "9 - Month Top Category Report\n";

		std::cout << ">>> ";
		std::cin >> ch;

		std::cin.ignore();

		int tmp;
		switch (ch)
		{
		case 1:
			std::cout << dayReport.ToString() << "\n";
			std::cout << "Do you want to save Report to the file (0 - No, 1 - Yes): ";
			std::cin >> tmp;
			if (tmp > 0)
			{
				char tmp2;
				if (reporter.SaveReportToFile(dayReport))
				{
					std::cout << "Report was saved!\n(Enter any char to continue)\n>>> ";
					std::cin >> tmp2;
				}
				else
				{
					std::cout << "File already exist\n(Enter any char to continue)\n>>> ";
					std::cin >> tmp2;
				}
			}
			break;
		case 2:
			std::cout << weekReport.ToString() << "\n";
			std::cout << "Do you want to save Report to the file (0 - No, 1 - Yes): ";
			std::cin >> tmp;
			if (tmp > 0)
			{
				char tmp2;
				if (reporter.SaveReportToFile(weekReport))
				{
					std::cout << "Report was saved!\n(Enter any char to continue)\n>>> ";
					std::cin >> tmp2;
				}
				else
				{
					std::cout << "File already exist\n(Enter any char to continue)\n>>> ";
					std::cin >> tmp2;
				}
			}
			break;
		case 3:
			std::cout << monthReport.ToString() << "\n";
			std::cout << "Do you want to save Report to the file (0 - No, 1 - Yes): ";
			std::cin >> tmp;
			if (tmp > 0)
			{
				char tmp2;
				if (reporter.SaveReportToFile(monthReport))
				{
					std::cout << "Report was saved!\n(Enter any char to continue)\n>>> ";
					std::cin >> tmp2;
				}
				else
				{
					std::cout << "File already exist\n(Enter any char to continue)\n>>> ";
					std::cin >> tmp2;
				}
			}
			break;
		case 4:
			std::cout << dayTopReport.ToString() << "\n";
			std::cout << "Do you want to save Report to the file (0 - No, 1 - Yes): ";
			std::cin >> tmp;
			if (tmp > 0)
			{
				char tmp2;
				if (reporter.SaveReportToFile(dayTopReport))
				{
					std::cout << "Report was saved!\n(Enter any char to continue)\n>>> ";
					std::cin >> tmp2;
				}
				else
				{
					std::cout << "File already exist\n(Enter any char to continue)\n>>> ";
					std::cin >> tmp2;
				}
			}
			break;
		case 5:
			std::cout << weekTopReport.ToString() << "\n";
			std::cout << "Do you want to save Report to the file (0 - No, 1 - Yes): ";
			std::cin >> tmp;
			if (tmp > 0)
			{
				char tmp2;
				if (reporter.SaveReportToFile(weekTopReport))
				{
					std::cout << "Report was saved!\n(Enter any char to continue)\n>>> ";
					std::cin >> tmp2;
				}
				else
				{
					std::cout << "File already exist\n(Enter any char to continue)\n>>> ";
					std::cin >> tmp2;
				}
			}
			break;
		case 6:
			std::cout << monthTopReport.ToString() << "\n";
			std::cout << "Do you want to save Report to the file (0 - No, 1 - Yes): ";
			std::cin >> tmp;
			if (tmp > 0)
			{
				char tmp2;
				if (reporter.SaveReportToFile(monthTopReport))
				{
					std::cout << "Report was saved!\n(Enter any char to continue)\n>>> ";
					std::cin >> tmp2;
				}
				else
				{
					std::cout << "File already exist\n(Enter any char to continue)\n>>> ";
					std::cin >> tmp2;
				}
			}
			break;
		case 7:
			std::cout << dayTopCategoryReport.ToString() << "\n";
			std::cout << "Do you want to save Report to the file (0 - No, 1 - Yes): ";
			std::cin >> tmp;
			if (tmp > 0)
			{
				char tmp2;
				if (reporter.SaveReportToFile(dayTopCategoryReport))
				{
					std::cout << "Report was saved!\n(Enter any char to continue)\n>>> ";
					std::cin >> tmp2;
				}
				else
				{
					std::cout << "File already exist\n(Enter any char to continue)\n>>> ";
					std::cin >> tmp2;
				}
			}
		case 8:
			std::cout << weekTopCategoryReport.ToString() << "\n";
			std::cout << "Do you want to save Report to the file (0 - No, 1 - Yes): ";
			std::cin >> tmp;
			if (tmp > 0)
			{
				char tmp2;
				if (reporter.SaveReportToFile(weekTopCategoryReport))
				{
					std::cout << "Report was saved!\n(Enter any char to continue)\n>>> ";
					std::cin >> tmp2;
				}
				else
				{
					std::cout << "File already exist\n(Enter any char to continue)\n>>> ";
					std::cin >> tmp2;
				}
			}
			break;
		case 9:
			std::cout << monthTopCategoryReport.ToString() << "\n";
			std::cout << "Do you want to save Report to the file (0 - No, 1 - Yes): ";
			std::cin >> tmp;
			if (tmp > 0)
			{
				char tmp2;
				if (reporter.SaveReportToFile(monthTopCategoryReport))
				{
					std::cout << "Report was saved!\n(Enter any char to continue)\n>>> ";
					std::cin >> tmp2;
				}
				else
				{
					std::cout << "File already exist\n(Enter any char to continue)\n>>> ";
					std::cin >> tmp2;
				}
			}
			break;
		default:
			break;
		}
	} while (ch != 0);
}

void FinanceSystem::DepositMenu(int index)
{
	int ch;
	do
	{
		system("cls");

		Account* account = accounts[index];

		std::string accountName = account->GetName();

		std::vector<MoneyStorage*> cardsArray = account->GetAllStoragesWithType(CARD);
		std::vector<MoneyStorage*> walletsArray = account->GetAllStoragesWithType(WALLET);

		std::cout << "Accaunts/" << accountName << "/Deposit\n\n";

		int i = 1;
		ShowTable(accountName, cardsArray, CARD, i);
		ShowTable(accountName, walletsArray, WALLET, i);

		std::cout << "Choose the Card/Wallet (0. Back):\n";

		std::cout << ">>> ";
		std::cin >> ch;

		std::cin.ignore();

		double sum = 0;
		int numOfCards = cardsArray.size();
		int numOfWallets = walletsArray.size();
		if (ch > 0 && ch <= numOfCards)
		{
			std::cout << "\nEnter the amount to top up:\n";
			std::cout << ">>> ";
			std::cin >> sum;

			cardsArray[ch - 1]->Deposit(sum);
		}
		else if (ch > numOfCards && ch <= numOfWallets + numOfCards)
		{
			std::cout << "\nEnter the amount to top up:\n";
			std::cout << ">>> ";
			std::cin >> sum;

			walletsArray[ch - numOfCards - 1]->Deposit(sum);
		}
	} while (ch != 0);
}

void FinanceSystem::WithdrawMenu(int index)
{
	int ch;
	do
	{
		system("cls");

		Account* account = accounts[index];

		std::string accountName = account->GetName();

		std::vector<MoneyStorage*> cardsArray = account->GetAllStoragesWithType(CARD);
		std::vector<MoneyStorage*> walletsArray = account->GetAllStoragesWithType(WALLET);

		std::cout << "Accaunts/" << accountName << "/Withdraw\n\n";

		bool withdrawSuccess = true;

		int i = 1;
		ShowTable(accountName, cardsArray, CARD, i);
		ShowTable(accountName, walletsArray, WALLET, i);

		std::cout << "Choose the Card/Wallet (0. Back):\n";

		std::cout << ">>> ";
		std::cin >> ch;

		std::cin.ignore();

		double sum = 0;
		int numOfCards = cardsArray.size();
		int numOfWallets = walletsArray.size();
		if (ch > 0 && ch <= numOfCards)
		{
			std::cout << "\nEnter the amount to withdraw:\n";
			std::cout << ">>> ";
			std::cin >> sum;

			withdrawSuccess = cardsArray[ch - 1]->Withdraw(sum);
		}
		else if (ch > numOfCards && ch <= numOfWallets + numOfCards)
		{
			std::cout << "\nEnter the amount to withdraw:\n";
			std::cout << ">>> ";
			std::cin >> sum;

			withdrawSuccess = walletsArray[ch - numOfCards - 1]->Withdraw(sum);
		}
		if (!withdrawSuccess)
		{
			char tmp;
			std::cout << "\nWithdrawal operation was not successfull\n"
				<< "Not enough money on the balance\n"
				<< "Enter any char to continue\n>>> ";
			std::cin >> tmp;
		}
	} while (ch != 0);
}

void FinanceSystem::NewExpanseMenu(int index)
{
	int ch;
	do
	{
		system("cls");

		Account* account = accounts[index];

		std::string accountName = account->GetName();

		std::vector<MoneyStorage*> cardsArray = account->GetAllStoragesWithType(CARD);
		std::vector<MoneyStorage*> walletsArray = account->GetAllStoragesWithType(WALLET);

		std::cout << "Accaunts/" << accountName << "/NewExpanse\n\n";

		int i = 1;
		ShowTable(accountName, cardsArray, CARD, i);
		ShowTable(accountName, walletsArray, WALLET, i);

		std::cout << "Choose the Card/Wallet (0. Back):\n";

		std::cout << ">>> ";
		std::cin >> ch;

		int numOfCards = cardsArray.size();
		int numOfWallets = walletsArray.size();
		if (ch > 0 && ch <= numOfCards)
		{
			cardsArray[ch - 1]->AddNewExpense();
		}
		else if (ch > numOfCards && ch <= numOfWallets + numOfCards)
		{
			walletsArray[ch - numOfCards - 1]->AddNewExpense();
		}
	} while (ch != 0);
}

void FinanceSystem::NewStorageMenu(Storage type, int index)
{
	std::cin.ignore();

	if (type == WALLET)
	{
		char ch;

		system("cls");

		Account* account = accounts[index];

		std::string accountName = account->GetName();

		MoneyStorage* storage = new Wallet();
		storage->Input();

		account->AddStorage(WALLET, storage);

		std::cout << "\nYour new Wallet:\n";
		std::cout << storage->ToString(true) << "\n";

		std::cin.ignore();
		std::cout << "Enter a char to continue\n>>> ";
		std::cin >> ch;
	}
	else if (type == CARD)
	{
		char ch;

		system("cls");

		Account* account = accounts[index];

		std::string accountName = account->GetName();

		MoneyStorage* storage = new Card();
		storage->Input();

		account->AddStorage(CARD, storage);

		std::cout << "\nYour new Card:\n";
		std::cout << storage->ToString(true) << "\n";

		std::cin.ignore();
		std::cout << "Enter a char to continue\n>>> ";
		std::cin >> ch;
	}
}

void FinanceSystem::ShowTable(std::string name, std::vector<MoneyStorage*>& storages, Storage type)
{
	if (type == CARD)
	{
		if (!storages.empty())
		{
			ConsoleTable cardsTable{ "Name", "Balance", "Currency", "Type", "Credit Limit" };

			for (auto& card : storages)
			{
				cardsTable +=
				{
					card->GetName(),
					std::to_string(card->GetBalance()),
					card->GetCurrency(),
					card->GetTypeName(),
					static_cast<Card*>(card)->IsCredit() ? // Only storages with type CARD, so i can use static_cast for sure
					std::to_string(static_cast<Card*>(card)->GetCreditLimit()) : "No"
				};
			}
			std::cout << center(name + "/Cards", cardsTable.getTableWidth() - 1) << "\n";
			std::cout << cardsTable << "\n";
		}
		else
			std::cout << name << " doesn't have any cards.\n\n";
	}
	else if (type == WALLET)
	{
		if (!storages.empty())
		{
			ConsoleTable walletsTable{ "Name", "Balance", "Currency", "Network", "Crypto" };

			for (auto& wallet : storages)
			{
				walletsTable +=
				{
					wallet->GetName(),
					std::to_string(wallet->GetBalance()),
					wallet->GetCurrency(),
					static_cast<Wallet*>(wallet)->GetNetwork(),
					static_cast<Wallet*>(wallet)->IsCrypto() ? "Yes" : "No"
				};
			}
			std::cout << center(name + "/Wallets", walletsTable.getTableWidth() - 1) << "\n";
			std::cout << walletsTable << "\n";
		}
		else
			std::cout << name << " doesn't have any wallets.\n\n";
	}
}

void FinanceSystem::ShowTable(std::string name, std::vector<MoneyStorage*>& storages, Storage type, int& index)
{
	if (type == CARD && !storages.empty())
	{
		ConsoleTable cardsTable{ "Index", "Name", "Balance", "Currency", "Type" };

		for (auto& card : storages)
		{
			cardsTable +=
			{
				std::to_string(index),
				card->GetName(),
				std::to_string(card->GetBalance()),
				card->GetCurrency(),
				card->GetTypeName()
			};
			index++;
		}
		std::cout << center(name + "/Cards", cardsTable.getTableWidth() - 1) << "\n";
		std::cout << cardsTable << "\n";
	}
	else if (type == WALLET && !storages.empty())
	{
		ConsoleTable walletsTable{ "Index", "Name", "Balance", "Currency" };

		for (auto& wallet : storages)
		{
			walletsTable +=
			{
				std::to_string(index),
				wallet->GetName(),
				std::to_string(wallet->GetBalance()),
				wallet->GetCurrency()
			};
			index++;
		}
		std::cout << center(name + "/Wallets", walletsTable.getTableWidth() - 1) << "\n";
		std::cout << walletsTable << "\n";
	}
}

FinanceSystem::~FinanceSystem()
{
	for (auto& account : accounts)
	{
		delete account;
	}
}
