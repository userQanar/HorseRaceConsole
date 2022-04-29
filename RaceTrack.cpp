#include "RaceTrack.h"

const RacingHorse& RaceTrack::race(const std::string& raceName,  Console& console, const immutableHorseList& horses, int length) {
    this->prepareRace(raceName, horses, length);

    RacingHorse* winnerHorse = NULL;
    bool winnerFound = false;

    console.clearScreen();
    this->printHeader(raceName, console, horses, length);

    // Circuit breaker, if we really mess up, the loop will eventually end somewhen
    unsigned int max_iteration = UINT32_MAX;
    for (unsigned int i = 0; i < max_iteration; i++) {
        if (winnerFound)
            break;
        for (auto horse : horses) {
            RacingHorse* horsii = &horse.get();
            RacingLane* lane = this->myTrack.find(horsii)->second;

            int oldProgress = horsii->getPosition();
            horsii->tick();

            if (horsii->getPosition() > oldProgress || i == 0) {
                lane->print(console, *horsii);
                console.out.flush();
            }

            if (!winnerFound) {
                winnerFound = horsii->getPosition() >= lane->getLength();
                if (winnerFound) winnerHorse = horsii;
            }
        }
    }

    this->cleanUpAfterRace();

    int nextNewRow = (this->makeHeaderLines(raceName, horses, length)).size() + horses.size() + 1;
    console.moveTo(nextNewRow, 1);
    
    //const RacingHorse& win = winnerHorse;
    return *winnerHorse;
}

const std::vector<std::string> RaceTrack::makeHeaderLines(const std::string& raceName, const immutableHorseList& horses, int length) {

    std::string horseCountAsStr = std::to_string(horses.size());
    std::string firstLine = "Willkommen beim Rennen von \"" + raceName + "\"";
    std::string secondLine = "Teilnehmer: " + horseCountAsStr + " auf einer Laenge von " + std::to_string(length) + " Sternen!";
    return std::vector<std::string>{
        firstLine,
            secondLine
    };
}

void RaceTrack::printHeader(const std::string& raceName, Console& console, const immutableHorseList& horses, int length) {
    auto headerlines = this->makeHeaderLines(raceName, horses, length);

    unsigned int counter = 1;
    for (auto headerline : headerlines) {
        console.moveTo(counter++, 0);
        console.out << headerline;
    }
}

int RaceTrack::race(const std::string& raceName, Console& console, RacingHorse& horseOne, RacingHorse& horseTwo, int length) {
    //const immutableHorseList myVector = { horseOne, horseTwo };
    std::vector<std::reference_wrapper<RacingHorse>> myVector{ horseOne, horseTwo };

    const std::vector<std::reference_wrapper<RacingHorse>>& myVectors = myVector;
    const RacingHorse& winner = this->race(raceName, console, myVectors, length);

    auto firstHorse = myVector[0].get();

    if (winner.getName() == firstHorse.getName()) return 0;
    return 1;
}

void RaceTrack::prepareRace(const std::string& raceName, const immutableHorseList& horses, int length) {

    auto headerLines = this->makeHeaderLines(raceName, horses, length);
    int counter = 1 + headerLines.size();
    for (auto horse : horses) {
        RacingHorse* horsii = &horse.get();
        RacingLane* horsesLane = new RacingLane(counter, 30, length);
        this->myTrack.insert(std::pair<RacingHorse*, RacingLane*>(horsii, horsesLane));

        horsii->prepare(horses,raceName,length);
        counter++;
    }
}

void RaceTrack::cleanUpAfterRace() {

    for (std::pair<RacingHorse*, RacingLane*> pair: this->myTrack) {
        pair.first->reset();
        delete pair.second;
    }
    this->myTrack.clear();
}