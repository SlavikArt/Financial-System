#pragma once

#include "MoneyStorage.h"

class Wallet :
    public MoneyStorage
{
    bool isCrypto;
    std::string networkName;
public:
    Wallet();
    Wallet(std::string id, std::string name,
        std::string currency, std::string typeName,
        std::string userName, bool isCrypto, std::string networkName);

    std::string GetNetwork();
    bool IsCrypto();

    std::string ToString(bool toTable = false);
    void Input();
};
