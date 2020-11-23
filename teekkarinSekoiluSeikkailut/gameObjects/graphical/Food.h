#ifndef FOOD_H
#define FOOD_H

#include <QTimer>
#include <QString>


class Food: public QObject
{
     Q_OBJECT
public:
    Food(int price, int foodStateChangeTimeInSeconds, int foodPriceFactorModifier);

    ~Food();

    int getPrice();
    int getState();

public slots:
    void foodStateTimeout();

signals:
    void foodStateChanged(Food *sender, int state);

private:
    const int HOT = 2;
    const int WARM = 1;
    const int COLD = 0;
    const int FOOD_PRICE_FACTOR_MODIFIER;

    int price_;
    QTimer foodStateTimer_;
    int foodStateChangeTimeInSeconds_;
    int state_;
};

#endif // FOOD_H
