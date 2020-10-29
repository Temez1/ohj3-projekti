#include "TeekkariHandler.h"

TeekkariHandler::TeekkariHandler(QList<Teekkari *> initTeekkarit, std::vector<Stop *> stops):
    teekkarit_(initTeekkarit),
    stops_(stops)
{
    if ( stops_.empty() ){
        throw std::invalid_argument("Stops can't be empty!");
    }
}
