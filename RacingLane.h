#pragma once

#include <memory>
#include <string>
#include "Console.h"
#include "Racer.h"

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
    void print(Console& console, Racer& horse);

    //bool constName = false; did lock the nameplates in the vector to not refresh
    //-> resulting in missing backward steps animation in polymorph race
};
