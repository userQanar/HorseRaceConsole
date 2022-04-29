#pragma once

#include <memory>
#include <string>
#include <vector>
#include <optional>

#include "Console.h"
#include "RacingJockey.h"

class RacingHorse {
private:

    std::string name;


    std::optional<RacingJockey> jockey;
    unsigned int position;
    unsigned int stepSize{ 1000000 };


    int calcStepMod(int dice100, unsigned int diceUnlim);
    const bool trueInXPercent(unsigned int percentage);

    bool step();

public:
    RacingHorse(const std::string& name);
    RacingHorse(const std::string& name, const RacingJockey& jockey);
    ~RacingHorse();

    std::string  getName() const;
    unsigned int getPosition();
    unsigned int getStepSize();
    std::optional<RacingJockey> getJockey();

    void tick();
    void print(const Console& console);
    void reset();

    void prepare(const std::vector<std::reference_wrapper<RacingHorse>>& horses, const std::string& racename, unsigned int length);


    //Buffs and Debuffs
    //Counters
    int trotting = 0;
    int running  = 0;
    int galloping= 0;
    //int airborne=0;//to be decided
    //int spine  = 0;//to be decided
    
    //Passives
    bool didPoo           = false;
    bool overweightJockey = false;
    bool obeseJockey      = false;
    int operator ==(RacingHorse that) const;
}; 