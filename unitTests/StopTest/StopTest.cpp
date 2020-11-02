#include <QtTest>

#include "gameObjects/graphical/Stop.h"

class StopTest : public QObject
{
    Q_OBJECT
public:
    StopTest();
    ~StopTest();

    Stop *stop;

private slots:
    void init();
    void cleanup();

    void addTeekkari_StopHasNoTeekkari_StopHasTeekkariAndReturnsTrue();
    void addTeekkari_StopHasTeekkari_StopHasTeekkariAndReturnsFalse();

    void removeTeekkari_StopHasTeekkari_StopHasNoTeekkariAndReturnsTrue();
    void removeTeekkari_StopHasNoTeekkari_StopHasNoTeekkariAndReturnsFalse();
};

StopTest::StopTest():
    stop(new Stop("test",QPointF(0,0)))
{}

StopTest::~StopTest()
{}

void StopTest::init()
{
    stop = new Stop("test", QPointF(0,0));
}

void StopTest::cleanup()
{
    delete stop;
}

void StopTest::addTeekkari_StopHasNoTeekkari_StopHasTeekkariAndReturnsTrue()
{
    auto addTeekkariReturnValue = stop->addTeekkari(new Teekkari());
    auto hasTeekkariReturnValue = stop->hasTeekkari();

    QCOMPARE(hasTeekkariReturnValue, true);
    QCOMPARE(addTeekkariReturnValue, true);
}

void StopTest::addTeekkari_StopHasTeekkari_StopHasTeekkariAndReturnsFalse()
{
    stop->addTeekkari(new Teekkari());

    auto addTeekkariReturnValue = stop->addTeekkari(new Teekkari());
    auto hasTeekkariReturnValue = stop->hasTeekkari();

    QCOMPARE(hasTeekkariReturnValue, true);
    QCOMPARE(addTeekkariReturnValue, false);
}

void StopTest::removeTeekkari_StopHasTeekkari_StopHasNoTeekkariAndReturnsTrue()
{
    stop->addTeekkari(new Teekkari());

    auto removeTeekkariReturnValue = stop->removeTeekkari();
    auto hasTeekkariReturnValue = stop->hasTeekkari();

    QCOMPARE(hasTeekkariReturnValue, false);
    QCOMPARE(removeTeekkariReturnValue, true);
}

void StopTest::removeTeekkari_StopHasNoTeekkari_StopHasNoTeekkariAndReturnsFalse()
{
    auto removeTeekkariReturnValue = stop->removeTeekkari();
    auto hasTeekkariReturnValue = stop->hasTeekkari();

    QCOMPARE(hasTeekkariReturnValue, false);
    QCOMPARE(removeTeekkariReturnValue, false);
}

QTEST_APPLESS_MAIN(StopTest)

#include "StopTest.moc"
