#ifndef BUSLINES_H
#define BUSLINES_H

#include <vector>
#include <unordered_map>
#include <string>

class BusLines
{
public:
    BusLines();

private:
    struct Coordinates{
        unsigned int x;
        unsigned int y;
    };

    struct Stop{
        Coordinates Coordinates;
        int time;
    };

    struct BusLine{
        std::vector<Stop> stops;
    };

    std::unordered_map<std::string, BusLine> *busLines_;

};

#endif // BUSLINES_H
