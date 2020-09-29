#include "peliikkuna.h"
#include "ui_peliikkuna.h"

PeliIkkuna::PeliIkkuna(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::peliIkkuna)
{
    ui->setupUi(this);
}

PeliIkkuna::~PeliIkkuna()
{
    delete ui;
}

