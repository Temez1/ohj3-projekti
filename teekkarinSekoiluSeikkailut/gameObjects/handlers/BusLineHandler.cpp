#include "BusLineHandler.h"

BusLineHandler::BusLineHandler(std::vector<std::shared_ptr<BusLine>> buslines):
    buslines_(buslines)
{

}

std::shared_ptr<BusLine> BusLineHandler::getRandomBusLine()
{
    return *std::next(std::begin(buslines_), rand()%(buslines_.size()));
}
