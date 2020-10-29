#include "TeekkariHandler.h"

TeekkariHandler::TeekkariHandler(QGraphicsScene *scene, std::vector<Stop *> stops, int initTeekkariAmount):
    INIT_TEEKKARI_AMOUNT(initTeekkariAmount),
    scene_(scene),
    stops_(stops)
{
    if ( stops_.empty() ){
        throw std::invalid_argument("Stops can't be empty!");
    }
    if (INIT_TEEKKARI_AMOUNT < 0){
        throw std::invalid_argument("Init tekkari amount can't be less than zero!");
    }

    srand(time(0));
    for (int i=0; i<INIT_TEEKKARI_AMOUNT; i++) {
        auto teekkari = new Teekkari();
        auto randomStop = *std::next(std::begin(stops_), rand()%(stops_.size()));
        teekkari->setPos(randomStop->pos());
        scene_->addItem(teekkari);
        teekkarit_.append(teekkari);
    }
}
