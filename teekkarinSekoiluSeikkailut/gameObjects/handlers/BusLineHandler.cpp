#include "BusLineHandler.h"

BusLineHandler::BusLineHandler(QString name, std::vector<Stop *> stops):
    name(name)
{
    if (not (stops.size() > 1) ){
        throw std::invalid_argument("Bus line must have at least two stops to create a line");
    }
    stops_ = stops;
    updateLastStop();
}

void BusLineHandler::addStop(Stop *stop)
{
    stops_.push_back(stop);
    updateLastStop();
}

std::pair<int,int> BusLineHandler::getNextStopIndexAndNewDirection(int currentStopIndex, int busDirection)
{
    checkIsBusDirectionValid(busDirection);
    checkIsStopIndexValid(currentStopIndex);

    if ( currentStopIndex == lastStopIndex ){
        return {currentStopIndex - 1, BUS_DIRECTION_FROM_END_TO_START_};
    }

    if ( currentStopIndex == FIRST_STOP_INDEX ){
        return {currentStopIndex + 1, BUS_DIRECTION_FROM_START_TO_END_};
    }

    if ( busDirection == BUS_DIRECTION_FROM_START_TO_END_ ){
        return {currentStopIndex + 1, BUS_DIRECTION_FROM_START_TO_END_};
    }

    if ( busDirection == BUS_DIRECTION_FROM_END_TO_START_ ){
        return {currentStopIndex - 1, BUS_DIRECTION_FROM_END_TO_START_};
    }

    throw std::logic_error("Logic error in program");
}

QPointF BusLineHandler::getStopPosition(int stopIndex)
{
    checkIsStopIndexValid(stopIndex);

    return stops_.at(stopIndex)->pos();
}

Stop *BusLineHandler::getStopByIndex(int stopIndex)
{
    checkIsStopIndexValid(stopIndex);
    return stops_.at(stopIndex);
}

Stop *BusLineHandler::getRandomStop()
{
    return *std::next(std::begin(stops_), rand()%(stops_.size()));
}

void BusLineHandler::checkIsBusDirectionValid(int busDirection)
{
    if ( not ( busDirection == BUS_DIRECTION_FROM_START_TO_END_ or
               busDirection == BUS_DIRECTION_FROM_END_TO_START_ ) ){
        throw std::invalid_argument("Bus direction invalid.");
    }
}

void BusLineHandler::checkIsStopIndexValid(int stopIndex)
{
    if ( stopIndex < 0 or stopIndex > lastStopIndex){
        throw std::out_of_range("Stop index out of range of stops");
    }
}

void BusLineHandler::updateLastStop()
{
    lastStopIndex = static_cast<int>(stops_.size()) - 1;
}
