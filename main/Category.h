#pragma once
#include <iostream>

enum CategoryType // TODO: add more categories
{
	None,
	CafesAndRestaurants,
	Grocery,
	Transaction,
	Other
};

std::string CategoryTypeToString(CategoryType type);

class Category
{
	CategoryType type;
	double cashbackPercentage;
public:
	Category();
	Category(CategoryType type, double cashbackPercentage = 0);

	CategoryType GetType();
	double GetCashbackPercentage();

	bool operator==(const Category& category);
};

inline std::string CategoryTypeToString(CategoryType type) // TODO: add more categories
{
	switch (type)
	{
	case None:
		return "None";
	case CafesAndRestaurants:
		return "Cafes And Restaurants";
	case Grocery:
		return "Grocery";
	case Transaction:
		return "Transaction";
	case Other:
		return "Other";
	default:
		return "";
	}
}
