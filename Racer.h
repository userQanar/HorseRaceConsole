#pragma once

#include <memory>
#include <string>
#include <vector>
#include <optional>

#include "Console.h"
#include "RacingJockey.h"

class Racer {
protected:
    //friend class RacingHorse; // keine Ahnung 
    std::string name;
    std::optional<RacingJockey> jockey;

    unsigned int position;
    unsigned int stepSize{ 10000 };


    int calcStepMod(int dice100, unsigned int diceUnlim);
    bool trueInXPercent(unsigned int percentage);

    virtual int step();

public:
    Racer(const std::string& name);
    Racer(const std::string& name, const RacingJockey& jockey);
    ~Racer();

    std::string  getName() const;
    unsigned int getPosition();
    unsigned int getStepSize();
    //std::optional<RacingJockey> getJockey();

    void tick();
    virtual void print(const Console& console);
    void reset();

    void prepare(const std::vector<std::reference_wrapper<Racer>>& horses, const std::string& racename, unsigned int length);
    int  operator ==(Racer that) const;

    //Buffs and Debuffs
    //Counters
    bool trottingBool = false;
    bool runningBool = false;
    bool gallopingBool = false;
    int trotting = 0;
    int running = 0;
    int galloping = 0;
    //int airborne=0;//to be decided
    //int spine  = 0;//to be decided

    //Passives
    bool didPoo = false;
    bool overweightJockey = false;
    bool obeseJockey = false;
};


class RacingHorse : public Racer {
public:

    using Racer::Racer;
};

class FrillLizard : public Racer {
public:

    int step();// minus coordinates crash loop
    void print(const Console& console);
    using Racer::Racer;
};

class RagingBull : public Racer {
public:

    int step();// minus coordinates crash loop
    void print(const Console& console);
    using Racer::Racer;
};