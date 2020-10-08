#include "BusLine.h"

BusLine::BusLine(QString name, std::vector<QGraphicsSvgItem *> stops):
    name(name)
{
    if (not (stops.size() > 1) ){
        throw std::invalid_argument("Bus line must have at least two stops to create a line");
    }
    stops_ = stops;
    updateLastStop();
}

void BusLine::addStop(QGraphicsSvgItem *stop)
{
    stops_.push_back(stop);
    updateLastStop();
}

int BusLine::getNextStop(int currentStop, int busDirection)
{
    checkIsBusDirectionValid(busDirection);

    if ( currentStop == lastStop ){
        return currentStop - 1;
    }

    if ( currentStop == FIRST_STOP_ ){
        return currentStop + 1;
    }

    if ( busDirection == BUS_DIRECTION_FROM_START_TO_END_ ){
        return currentStop + 1;
    }

    if ( busDirection == BUS_DIRECTION_FROM_END_TO_START_ ){
        return currentStop - 1;
    }

    throw std::logic_error("Logic error in program");
}

void BusLine::checkIsBusDirectionValid(int busDirection)
{
    if ( not ( busDirection == BUS_DIRECTION_FROM_START_TO_END_ or
               busDirection == BUS_DIRECTION_FROM_END_TO_START_ ) ){
        throw std::invalid_argument("Bus direction invalid.");
    }
}

void BusLine::updateLastStop()
{
    lastStop = static_cast<int>(stops_.size()) - 1;
}
