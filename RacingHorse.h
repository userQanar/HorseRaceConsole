#pragma once

#include <memory>
#include <string>
#include "Console.h"

class RacingHorse {
private:
    std::string name;
    unsigned int position;
    static const unsigned int stepSize{ 1000000 };

    bool step();
public:
    RacingHorse(std::string name);
    ~RacingHorse();

    std::string          getName();
    unsigned int     getPosition();
    static const int getStepSize();

    void tick();
    void print(const Console& console);
    void reset();

    //Buffs and Debuffs
    //Counters
    int trotting = 0;
    int running  = 0;
    int galloping= 0;
    //int airborne=0;//to be decided
    //int spine  = 0;//to be decided
    
    //Passives
    bool preperation      = true;
    bool didPoo           = false;
    bool overweightJockey = false;
    bool obeseJockey      = false;
    bool winnerFirstGame  = false;
};