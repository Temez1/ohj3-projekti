#include "Wallet.h"

Wallet::Wallet(int StartingMoney):
    balance_(StartingMoney)
{

}

bool Wallet::pay(int amount)
{
    if (amount > balance_){
        return false;
    }

    balance_ -= amount;
    return true;
}

void Wallet::receive(unsigned int amount)
{
    balance_ += amount;
}

int Wallet::getBalance()
{
    return balance_;
}

