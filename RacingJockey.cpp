#include "RacingJockey.h"

RacingJockey::RacingJockey(const std::string& name)
: name(name),
  weight(75)
{}

RacingJockey::RacingJockey(const std::string& name, const unsigned int weight)
: name(name),
  weight(weight)
{}


const std::string RacingJockey::getName() const{
    return this->name;
}

unsigned int RacingJockey::getWeight() const{
    return this->weight;
}

// NOT USED 
const unsigned int RacingJockey::getSpeedFactor() const {
    if (this->weight < 65) 
        return 100;
    if (this->weight < 80) 
        return 80;
    if (this->weight < 95) 
        return 60;
    return 30;
}

JockeyWeight RacingJockey::getWeightCategory() const {
    if (this->weight < 65) 
        return THIN;
    if (this->weight < 80) 
        return MEDIUM;
    if (this->weight < 95) 
        return THICC;
    return OBESE;
}