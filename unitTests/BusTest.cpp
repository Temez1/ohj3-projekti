#include <QTest>

#include "Bus.h"
#include "BusLine.h"

class BusTest : public QObject
{
    Q_OBJECT
public:
    BusTest();

private slots:
    void init();
    void cleanup();


private:
    Bus bus_;
};

BusTest::BusTest():
    bus_(Bus("Test", std::unique_ptr<>))
{}
