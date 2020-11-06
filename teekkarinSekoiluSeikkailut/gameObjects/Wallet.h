#ifndef WALLET_H
#define WALLET_H

#include <QObject>

class Wallet: public QObject
{
public:
    Wallet(int StartingMoney);

    bool pay(int amount);
    void receive(unsigned int amount);

    int getBalance();

signals:
    void balanceChanged(int balance);

private:
    int balance_;
};

#endif // WALLET_H
