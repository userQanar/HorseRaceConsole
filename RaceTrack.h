#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include "Console.h"
#include "RacingHorse.h"
#include "RacingLane.h"

using immutableHorseList = std::vector<std::reference_wrapper<RacingHorse>>;

class RaceTrack {
private:
    std::map<RacingHorse*, RacingLane*> myTrack;
    void prepareRace(const std::string& raceName, const immutableHorseList& horses, int length);
    void printHeader(const std::string& raceName, Console& console, const immutableHorseList& horses, int length);
    const std::vector<std::string> makeHeaderLines(const std::string& raceName, const immutableHorseList& horses, int length);

    void cleanUpAfterRace();

public:
    const RacingHorse& race(const std::string& raceName, Console& console, const immutableHorseList& horses, int length);
    int race(const std::string& raceName, Console& console, RacingHorse& horseOne, RacingHorse& horseTwo, int length);
};