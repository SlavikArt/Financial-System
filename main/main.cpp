#include "FinanceSystem.h"

int main()
{
    srand(time(0));
    
    // Random data for the expenses for the reports
    MoneyStorage* card = new Card("212321", "Salaries", "USD", "Visa Gold", "Viacheslav", 500);
    for (int i = None + 1; i <= Other; i++)
    {
        for (int j = 0; j < 5; j++)
            card->AddExpense(
                new Expense(
                    "MyExpanse #" + std::to_string(rand() % 100),
                    Category(static_cast<CategoryType>(i)),
                    Date(
                        rand() % 8 + 18,
                        rand() % 2 + 4,
                        2023
                    ),
                    Time(
                        rand() % 24,
                        rand() % 59,
                        rand() % 59
                    ),
                    rand() % 1000,
                    rand() % 1000
                )
            );

    }
    
    MoneyStorage* wallet = new Wallet("212321", "Savings", "EUR", "Simple", "Viacheslav", false, "Euro");
    for (int i = None + 1; i <= Other; i++)
    {
        for (int j = 0; j < 5; j++)
            wallet->AddExpense(
                new Expense(
                    "MyExpanse #" + std::to_string(rand() % 100 + 100),
                    Category(static_cast<CategoryType>(i)),
                    Date(
                        rand() % 8 + 18,
                        rand() % 3 + 4,
                        2023
                    ),
                    Time(
                        rand() % 24,
                        rand() % 59,
                        rand() % 59
                    ),
                    rand() % 1000 + rand() % 500,
                    rand() % 1000 + rand() % 500
                )
            );
    }

    std::vector<Account*> acs = { new Account{"Viacheslav"}, new Account{"Vika"} };
    acs[0]->AddStorage(CARD, card);
    acs[0]->AddStorage(WALLET, wallet);

    FinanceSystem system(acs);
    system.ShowMenu();
}
