#include "RaceTrack.h"

RacingHorse* RaceTrack::race(std::string raceName, Console& console, std::vector<RacingHorse*> horses, int length) {
    this->initRaceTrack(raceName, horses, length);
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
            RacingHorse* horsii = horse;
            RacingLane* lane = this->myTrack.find(horsii)->second;

            int oldProgress = horsii->getPosition();
            horsii->tick();

            if (horsii->getPosition() > oldProgress || i == 0) {
                lane->print(console, *horsii);
                console.out.flush();
            }

            bool hasWin = horsii->getPosition() >= lane->getLength();
            if (hasWin) {
                winnerFound = true;
                winnerHorse = horsii;
            }
        }
    }
    this->cleanUpAfterRace(horses);
    console.moveTo((this->makeHeaderLines(raceName, horses, length)).size() + horses.size() + 1, 1);
    return winnerHorse;
}

std::vector<std::string> RaceTrack::makeHeaderLines(std::string raceName, std::vector<RacingHorse*> horses, int length) {

    std::string horseCountAsStr = std::to_string(horses.size());
    std::string firstLine = "Willkommen beim Rennen von \"" + raceName + "\"";
    std::string secondLine = "Teilnehmer: " + horseCountAsStr + " auf einer Laenge von " + std::to_string(length) + " Sternen!";
    return std::vector<std::string>{
        firstLine,
            secondLine
    };
}

void RaceTrack::printHeader(std::string raceName, Console& console, std::vector<RacingHorse*> horses, int length) {
    auto headerlines = this->makeHeaderLines(raceName, horses, length);

    unsigned int counter = 1;
    for (auto headerline : headerlines) {
        console.moveTo(counter++, 0);
        console.out << headerline;
    }
}

int RaceTrack::race(std::string raceName, Console& console, RacingHorse horseOne, RacingHorse horseTwo, int length) {
    std::vector<RacingHorse*> myVector{ &horseOne, &horseTwo };
    RacingHorse* winner = this->race(raceName, console, myVector, length);
    if (winner == myVector[0]) return 0;
    return 1;
}

void RaceTrack::initRaceTrack(std::string raceName, std::vector<RacingHorse*> horses, int length) {

    auto headerLines = this->makeHeaderLines(raceName, horses, length);

    int counter = 1 + headerLines.size();
    for (RacingHorse* horse : horses) {
        RacingLane* horsesLane = new RacingLane(counter, 30, length);
        this->myTrack.insert(std::pair<RacingHorse*, RacingLane*>(horse, horsesLane));
        counter++;
    }
}

void RaceTrack::cleanUpAfterRace(std::vector<RacingHorse*> horses) {
    for (RacingHorse* horse : horses) {
        horse->reset();
        // Delete existing Lanes, if any
        auto maybehorseLanePair = this->myTrack.find(horse);
        if (maybehorseLanePair != this->myTrack.end()) {
            auto horseLanePair = *maybehorseLanePair;
            delete horseLanePair.second;
        }
    }
    this->myTrack.clear();
}