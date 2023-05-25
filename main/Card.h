#pragma once

#include "MoneyStorage.h"

class Card :
    public MoneyStorage
{
    bool isCredit; //std::string type; // Credit / Debit  // or bool isCredit = true / false
    double creditLimit; // 0 if type == Debit  // or bool isCredit = false
    double maxCreditLimit;
    // TODO: add credit limit maximum and this above will be current
public:
    Card();
    Card(std::string id, std::string name, 
        std::string currency, std::string typeName, 
        std::string userName, double maxCreditLimit = 0);

    bool IsCredit();
    double GetCreditLimit();

    std::string ToString(bool toTable = false);
    void Input();
};
