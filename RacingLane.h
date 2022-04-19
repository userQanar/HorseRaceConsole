#pragma once

#include <memory>
#include <string>
#include "Console.h"
#include "RacingHorse.h"

class RacingLane {
private:
    int laneNumber;
    int startPos;
    int length;

public:
    RacingLane(
        int laneNumber,
        int startPos,
        int length
    );
    ~RacingLane();

    int getLength();
    const void print(Console& console, RacingHorse& horse);
};