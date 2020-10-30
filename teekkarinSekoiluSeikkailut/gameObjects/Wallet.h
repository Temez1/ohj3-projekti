#ifndef WALLET_H
#define WALLET_H


class Wallet
{
public:
    Wallet(int StartingMoney);

    bool pay(int amount);
    int getBalance();

private:
    int balance_;
};

#endif // WALLET_H
