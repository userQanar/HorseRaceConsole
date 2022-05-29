#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include "Console.h"
#include "Racer.h"
#include "RacingLane.h"

using immutableHorseList = std::vector<std::reference_wrapper<Racer>>;

class RaceTrack {
private:
    std::map<Racer*, RacingLane*> myTrack;
    void prepareRace(const std::string& raceName, const immutableHorseList& horses, unsigned int length);
    void printHeader(const std::string& raceName, Console& console, const immutableHorseList& horses, unsigned int length);
    const std::vector<std::string> makeHeaderLines(const std::string& raceName, const immutableHorseList& horses, unsigned int length);

    void cleanUpAfterRace();

public:
    const Racer& race(const std::string& raceName, Console& console, const immutableHorseList& horses, unsigned int length);
    int race(const std::string& raceName, Console& console, Racer& horseOne, Racer& horseTwo, unsigned int length);
};