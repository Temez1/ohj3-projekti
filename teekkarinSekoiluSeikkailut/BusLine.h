#ifndef BUSLINES_H
#define BUSLINES_H

#include <vector>
#include <QString>
#include <QGraphicsSvgItem>

class BusLine
{
public:
    BusLine(QString name);
    QString name;

    void addStop(QGraphicsSvgItem *stop);

private:
    std::vector<QGraphicsSvgItem *> stops_;
};

#endif // BUSLINES_H
