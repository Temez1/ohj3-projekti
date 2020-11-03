#ifndef BUSLINEHANDLER_H
#define BUSLINEHANDLER_H

#include "gameObjects/BusLine.h"

class BusLineHandler
{
public:
    BusLineHandler(std::vector<std::shared_ptr<BusLine>> buslines);

    std::shared_ptr<BusLine> getRandomBusLine();
private:
    std::vector<std::shared_ptr<BusLine>> buslines_;
};

#endif // BUSLINEHANDLER_H
