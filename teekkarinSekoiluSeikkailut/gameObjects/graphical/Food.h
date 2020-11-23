#ifndef FOOD_H
#define FOOD_H

#include <QTimer>
#include <QString>


class Food: public QObject
{
     Q_OBJECT
public:
    Food(int price, int foodStateChangeTimeInSeconds, double foodPriceFactorModifier);

    ~Food();

    double getPrice();
    int getState();

public slots:
    void foodStateTimeout();

signals:
    void foodStateChanged(int state);

private:
    const int HOT = 2;
    const int WARM = 1;
    const int COLD = 0;
    const double FOOD_PRICE_FACTOR_MODIFIER;

    int price_;
    QTimer foodStateTimer_;
    int foodStateChangeTimeInSeconds_;
    int state_;
};

#endif // FOOD_H
