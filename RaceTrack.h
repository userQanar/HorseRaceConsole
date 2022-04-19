#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>
#include "Console.h"
#include "RacingHorse.h"
#include "RacingLane.h"

class RaceTrack {
private:
    std::map<RacingHorse*, RacingLane*> myTrack;
    void initRaceTrack(std::string raceName, std::vector<RacingHorse*> horses, int length);
    void printHeader(std::string raceName, Console& console, std::vector<RacingHorse*> horses, int length);
    std::vector<std::string> makeHeaderLines(std::string raceName, std::vector<RacingHorse*> horses, int length);

    void cleanUpAfterRace(std::vector<RacingHorse*> horses);

public:
    RacingHorse* race(std::string raceName, Console& console, std::vector<RacingHorse*> horses, int length);
    int race(std::string raceName, Console& console, RacingHorse horseOne, RacingHorse horseTwo, int length);
};