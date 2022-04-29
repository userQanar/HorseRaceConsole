#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Console.h"

enum JockeyWeight {
    THIN,
    MEDIUM,
    THICC,
    OBESE
};

class RacingJockey {
    public:
        RacingJockey(const std::string& name);
        RacingJockey(const std::string& name, const unsigned int weight);
    
        const std::string getName() const;
        unsigned int getWeight() const;

        const unsigned int getSpeedFactor() const;

        JockeyWeight getWeightCategory() const;
    
    private:
        const std::string name;
        const unsigned int weight;
};