#pragma once

#include <memory>
#include <string>
#include "Console.h"
#include "RacingHorse.h"

class RacingLane {
private:
    int laneNumber;
    int startPos;
    unsigned int length;

public:
    RacingLane(
        int laneNumber,
        int startPos,
        unsigned int length
    );
    ~RacingLane();

    unsigned int getLength();
    void print(Console& console, RacingHorse& horse);
};