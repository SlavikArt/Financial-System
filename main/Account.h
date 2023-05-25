#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include "MoneyStorage.h"

enum Storage
{
	CARD,
	WALLET
};

class Account
{
	std::string name; // Viacheslav
	std::map<Storage, std::vector<MoneyStorage*>> storages; // Cards and Wallets
public:
	Account(std::string name);
	Account(std::string name, Storage type, std::vector<MoneyStorage*> storages);

	std::string GetName();

	std::vector<MoneyStorage*> GetAllStorages(); // Account.GetAllStorages()
	std::vector<MoneyStorage*> GetAllStoragesWithType(Storage type); // Account.GetAllStoragesWithType(Storage.WALLET)
	MoneyStorage* GetStorageByName(std::string name); // Account.GetStorageByName("Salaries") // TODO: make name of the storage unique or add type parameter
	
	bool HasStoragesWithType(Storage type);

	void AddStorage(Storage type, MoneyStorage* storage); // Account.AddStorage(Storage.CARD, new Card(...))
	
	~Account();
};
