#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QProgressBar>

class ProgressBar : public QProgressBar
{
    Q_OBJECT
public:
    ProgressBar(QWidget *parent = nullptr);

public slots:
    void walletBalanceChanged(int balance);

signals:
    void enoughMoneyToPayStudentLoan();
};

#endif // PROGRESSBAR_H
