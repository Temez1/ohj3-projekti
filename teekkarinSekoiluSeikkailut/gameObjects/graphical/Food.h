#ifndef FOOD_H
#define FOOD_H

#include <QTimer>
#include <Qstring>


class Food: public QObject
{
     Q_OBJECT
public:
    Food(int price, int foodStateChangeTimeInSeconds);

    ~Food();

    int getPrice();
    int getState();

private slots:
    void foodStateTimeout();

signals:
    void foodStateChanged(Food *sender, int state);

private:
    const int HOT = 2;
    const int WARM = 1;
    const int COLD = 0;
    int price_;
    QTimer foodStateTimer_;
    int foodStateChangeTimeInSeconds_;
    int state_;
};

#endif // FOOD_H
