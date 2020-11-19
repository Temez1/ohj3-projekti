#include "ProgressBar.h"

ProgressBar::ProgressBar(QWidget *parent): QProgressBar(parent)
{

}

void ProgressBar::walletBalanceChanged(int balance)
{
    if (balance >= maximum()){
        setValue(maximum());
        emit enoughMoneyToPayStudentLoan();
        return;
    }
    setValue(balance);
}
