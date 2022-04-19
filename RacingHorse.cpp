#include "RacingHorse.h"

RacingHorse::RacingHorse(std::string name) :
    name(name),
    position(1)
{}

RacingHorse::~RacingHorse() {
    this->name.clear();
}

std::string RacingHorse::getName() {
    return this->name;
}

unsigned int RacingHorse::getPosition() {
    return this->position;
}

const int RacingHorse::getStepSize() {
    return RacingHorse::stepSize;
}

bool RacingHorse::step() {
    unsigned int n = RacingHorse::getStepSize();

    int speedBuff = (unsigned int)std::rand() % 100;

    if (preperation) {

        if (!overweightJockey) {
            if (speedBuff % 10 >= 0 && speedBuff % 10 <= 2) {
                this->overweightJockey = true;
            }
        }
        if (!obeseJockey) {
            if (speedBuff % 10 == 3 || speedBuff % 10 == 4) {
                this->obeseJockey = true;
            }
        }
        if (speedBuff > 40) {
            this->preperation = false;
            this->didPoo = true;
            return true;//Free Step Boost when pood in preMatch
        }
        else {
            this->preperation = false;//remove opening of the IF-Trees millions of times
        }
    }
    //Movement Abilitys
    if (speedBuff < 27) { 
        int mod = (unsigned int)std::rand() % (n * 7 / 8);//25 % Speedboost
        if (mod < 1) { this->trotting++; }
        return mod < 1 ? true : false;
    }
    else if (speedBuff > 27 && speedBuff < 40) { 
        int mod = (unsigned int)std::rand() % (n * 6 / 8);//50 % Speedboost
        if (mod < 1) { this->running++; }
        return mod < 1 ? true : false;
    }
    else if (speedBuff >= 40 && speedBuff < 47) { 
        int mod = (unsigned int)std::rand() % (n * 4 / 8);//100 % Speedboost
        if (mod < 1) { this->galloping++; }
        return mod < 1 ? true : false;
    }
    //Weight Modifiers
    else {

        if (overweightJockey) {
            int mod = (unsigned int)std::rand() % (n * 51 / 50);
            return mod < 1 ? true : false;// +3 Damage to this->Spine
        }
        else if (obeseJockey) {
            int mod = (unsigned int)std::rand() % (n * 21 / 20);
            return mod < 1 ? true : false;// +11 Damage to this->Spine
        }
        else if (winnerFirstGame) {
            int mod = (unsigned int)std::rand() % (n * 10 / 11);
            return mod < 1 ? true : false;// +9,09% increased Movementspeed of regularStep
        }// Winner Horse gets "Handicapped" for increased muscle contraction-> increased Speed.
        else {
            int mod = (unsigned int)std::rand() % n;
            return mod < 1 ? true : false;//regularStep
        }
    }
}

void RacingHorse::tick() {
    bool stepResult = this->step();
    this->position += stepResult;
}

void RacingHorse::print(const Console& console) {
    std::string asterics(this->position, '*');
    console.out << asterics;//Walking Animation
}

void RacingHorse::reset() {
    this->position = 1;
}

/*//Savegame normal Step\\
bool RacingHorse::step() {
   unsigned int n = RacingHorse::getStepSize();
   int mod = (unsigned int)std::rand() % n;
   return mod < 1 ? true : false;
}*/

/* @Brief 
Zwei Drittel der M�nner (67 %) und die H�lfte der Frauen (53 %) in Deutschland sind �bergewichtig.      // gerundet ~50% f�r Horse->weightModifier Frauen wiegen weniger in kg
Ein Viertel der Erwachsenen (23 % der M�nner und 24 % der Frauen) ist stark �bergewichtig (adip�s).     // gerundet ~20% f�r Horse->weightModifier Frauen wiegen weniger in kg

�bergewicht und Adipositas sind Mitursache f�r viele Beschwerden und k�nnen die Entwicklung chronischer Krankheiten beg�nstigen.
Aufgrund der steigenden Pr�valenz und den damit verbundenen Folgeerkrankungen entstehen betr�chtliche Kosten f�r das Gesundheits- und Sozialsystem.
�bergewicht und Adipositas sind daher Themen von hoher Public-Health-Relevanz.

Das Robert Koch-Institut erhebt im Rahmen des Gesundheitsmonitorings regelm��ig Daten zu �bergewicht und Adipositas.
In den Auswertungen des RKI geht es um mehr als nur um die Pr�valenz:
Zusammenh�nge zu anderen Lebensparametern, wie beispielsweise Bewegung, Ern�hrungsverhalten oder sozialer Status werden erforscht.
Quelle: � Robert Koch-Institut 2014, Studie DEGS1, Erhebung 2008�2011

if (obese && movementSpeedAbility){
+# Damage to this->Spine
Damage Values +3 trotting +7 running +13 galloping
return sumOfDamage;
}

countWins if-> more tournaments for buff stacking

if (winnerHorse->didntPoopFirstRace){
winnerHorse->needsToPoop = true
}//->main probably //doesnt need 2 speed buffs after getting winner boost

 if gekackt -> 60% chance gekackt zu haben -> deactivate mussKacken -> erster Step true  <- done
 if dickerReiter -> 2% Chance den else normaler Step zu verkacken 5% bei b�s adip�s <-done
 if winnerFirstGame -> 9,09% boost to regularStep <- done
*/