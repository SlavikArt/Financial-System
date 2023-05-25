#include "Account.h"

Account::Account(std::string name) : name(name) {}

Account::Account(std::string name, Storage type, std::vector<MoneyStorage*> storages) : name(name)
{
	for (auto& storage : storages)
		AddStorage(type, storage);
}

std::string Account::GetName()
{
	return name;
}

std::vector<MoneyStorage*> Account::GetAllStorages()
{
	std::vector<MoneyStorage*> allStorages;
	for (auto pair : storages)
	{
		allStorages.insert(allStorages.end(), pair.second.begin(), pair.second.end());
	}
	return allStorages;
}

std::vector<MoneyStorage*> Account::GetAllStoragesWithType(Storage type)
{
	return storages[type];
}

MoneyStorage* Account::GetStorageByName(std::string name)
{
	for (auto& pair : storages)
	{
		for (auto& storage : pair.second)
		{
			if (storage->GetName() == name)
			{
				return storage;
			}
		}
	}
	return nullptr;
}

bool Account::HasStoragesWithType(Storage type)
{
	return this->storages[type].empty();
}

void Account::AddStorage(Storage type, MoneyStorage* storage)
{
	storages[type].push_back(storage);
}

Account::~Account()
{
	for (auto& pair : storages)
	{
		for (auto& storage : pair.second)
		{
			delete storage;
		}
	}
}
