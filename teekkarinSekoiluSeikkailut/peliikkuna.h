#ifndef PELIIKKUNA_H
#define PELIIKKUNA_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class peliIkkuna; }
QT_END_NAMESPACE

class PeliIkkuna : public QMainWindow
{
    Q_OBJECT

public:
    PeliIkkuna(QWidget *parent = nullptr);
    ~PeliIkkuna();

private:
    Ui::peliIkkuna *ui;
};
#endif // PELIIKKUNA_H
