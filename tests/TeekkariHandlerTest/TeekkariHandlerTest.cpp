#include <QtTest>
#include <QCoreApplication>
#include <QGraphicsScene>

#include "gameObjects/handlers/TeekkariHandler.h"

class TeekkariHandlerTest : public QObject
{
    Q_OBJECT

public:
    const int INIT_TEEKKARI_AMOUNT = 2;
    const int TEEKKARI_SPAWN_TIME_IN_SECONDS = 20;
    const int MAX_AMOUNT_OF_TEEKKARIT_IN_THE_MAP = 2;

    TeekkariHandlerTest();
    ~TeekkariHandlerTest();

private slots:
    void init();
    void cleanup();

    void TeekkariHandler_init_TeekkaritInTheMapEqualsInitTeekkariAmount();

private:
    QGraphicsScene *scene_;
    Stop *firstStop_;
    Stop *secondStop_;
    std::shared_ptr<BusLine> busline_;
    std::shared_ptr<BusLineHandler> busLineHandler_;
    TeekkariHandler *teekkariHandler_;
};

TeekkariHandlerTest::TeekkariHandlerTest():
    scene_(new QGraphicsScene()),
    firstStop_(new Stop(QString("testStop1"), QPointF(100,100))),
    secondStop_(new Stop(QString("testStop2"), QPointF(200,100))),
    busline_(std::make_shared<BusLine>(BusLine(QString("3"), {firstStop_, secondStop_}))),
    busLineHandler_(std::make_shared<BusLineHandler>(BusLineHandler({busline_}))),
    teekkariHandler_(new TeekkariHandler(scene_, busLineHandler_, INIT_TEEKKARI_AMOUNT,
                                         TEEKKARI_SPAWN_TIME_IN_SECONDS, MAX_AMOUNT_OF_TEEKKARIT_IN_THE_MAP))
{}

TeekkariHandlerTest::~TeekkariHandlerTest()
{}

void TeekkariHandlerTest::init()
{
    scene_ = new QGraphicsScene();
    firstStop_ = new Stop(QString("testStop1"), QPointF(100,100));
    secondStop_ = new Stop(QString("testStop2"), QPointF(200,100));
    busline_ = std::make_shared<BusLine>(BusLine(QString("3"), {firstStop_, secondStop_}));
    busLineHandler_ = std::make_shared<BusLineHandler>(BusLineHandler({busline_}));
    teekkariHandler_ = new TeekkariHandler(scene_, busLineHandler_, INIT_TEEKKARI_AMOUNT,
                                           TEEKKARI_SPAWN_TIME_IN_SECONDS, MAX_AMOUNT_OF_TEEKKARIT_IN_THE_MAP);
}

void TeekkariHandlerTest::cleanup()
{
    delete scene_;
    delete firstStop_;
    delete secondStop_;
    delete teekkariHandler_;
}

void TeekkariHandlerTest::TeekkariHandler_init_TeekkaritInTheMapEqualsInitTeekkariAmount()
{
    auto teekkaritAmount = teekkariHandler_->getTeekkaritAmount();

    QCOMPARE(teekkaritAmount, INIT_TEEKKARI_AMOUNT);
}

QTEST_MAIN(TeekkariHandlerTest)

#include "TeekkariHandlerTest.moc"
