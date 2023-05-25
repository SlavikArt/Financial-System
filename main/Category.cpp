#include "Category.h"

Category::Category() : type(None), cashbackPercentage(0) {}

Category::Category(CategoryType type, double cashbackPercentage) 
    : type(type), cashbackPercentage(cashbackPercentage) 
{
    if (cashbackPercentage == 0)
    {
        switch (type)
        {
        case None:
            cashbackPercentage = 0;
            break;
        case CafesAndRestaurants:
            cashbackPercentage = 5;
            break;
        case Grocery:
            cashbackPercentage = 3;
            break;
        case Transaction:
            cashbackPercentage = 0;
            break;
        case Other:
            cashbackPercentage = 2;
            break;
        default:
            break;
        }
    }
}

CategoryType Category::GetType()
{
    return this->type;
}

double Category::GetCashbackPercentage()
{
    return this->cashbackPercentage;
}

bool Category::operator==(const Category& category)
{
    return this->type == category.type
        && this->cashbackPercentage == category.cashbackPercentage;
}
