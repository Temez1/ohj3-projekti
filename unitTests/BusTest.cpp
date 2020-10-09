#include "AutoTest.h"
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
    Bus *bus_;
};

BusTest::BusTest():
    bus_(new Bus("Test Bus", std::make_shared<BusLine>(BusLine("Test busline", {2, new QGraphicsSvgItem()}))))
{}

void BusTest::init()
{
    bus_ = new Bus("Test Bus", std::make_shared<BusLine>(BusLine("Test busline", {2, new QGraphicsSvgItem()})));
}

void BusTest::cleanup()
{
    delete bus_;
}

DECLARE_TEST(BusTest)

#include "BusTest.moc"
