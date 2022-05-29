#include "RacingLane.h"

RacingLane::RacingLane(
    int laneNumber,
    int startPos,
    unsigned int length
) : laneNumber(laneNumber)
, startPos(startPos)
, length(length)
{}



RacingLane::~RacingLane() {}

unsigned int RacingLane::getLength() {
    return this->length;
}

void RacingLane::print(Console& console, Racer& horse) {

        console.moveTo(this->laneNumber, 0);
        console.clearLine();
        console.out << horse.getName();

    console.moveTo(this->laneNumber, this->startPos);
    console.out << '|';
    horse.print(console);

    console.moveTo(this->laneNumber, this->startPos + this->length + 1);
    console.out << '|';

    if (horse.getPosition() >= this->length)
        console.out << " WINNER!";
}