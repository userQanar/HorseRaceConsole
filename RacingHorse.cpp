#include "RacingHorse.h"

RacingHorse::RacingHorse(const std::string& name) :
    name(name),
    jockey(std::nullopt),
    position(1)
{}

RacingHorse::RacingHorse(const std::string& name, const RacingJockey& jockey):
    name(name),
    jockey(jockey),
    position(1)
{}

RacingHorse::~RacingHorse() {
    this->name.clear();
    if (this->jockey.has_value())
        this->jockey.reset();
}

std::string RacingHorse::getName() const {
    return this->name;
}

unsigned int RacingHorse::getPosition() {
    return this->position;
}

unsigned int RacingHorse::getStepSize() {
    return RacingHorse::stepSize;
}

bool  RacingHorse::trueInXPercent(unsigned int percentage) {
    auto dice100 = (unsigned int)std::rand() % 100;
	return dice100 <= percentage;
}

int RacingHorse::calcStepMod(int dice100, unsigned int diceUnlim){
    unsigned int n = this->getStepSize();
    //unsigned int n = (double) this->getStepSize();

    // If the Horse has no jockey, it might either be faster, equally fast, or slower
    // Depending if horse is insane or epic
    // Values ranging between 49, 50, 51 -> Either -0.2%, no change, or +0.2%
    if (!this->jockey.has_value()) {
        float factor = ( (float) (dice100 % 3) + 49.0f) / 50.0f;
        n *= factor;
    } else {
        JockeyWeight weight = this->jockey->getWeightCategory();
        if (weight == THIN)
            n *= 3.0f/4.0f;
        if (weight == THICC)
            n *= 4.0f/3.0f;
        if (weight == OBESE)
            n *= 5.0f/3.0f;
    }


    //Movement Abilitys
    if (this->trueInXPercent(7)) {
        // Galloping
        this->galloping++; // Kinda wrong here. Step könnte theoretitsch nich gemacht werden, wird trotzdem in stats aufgenommen..
		n *= (float) 1 / 2; // -50%
    } else if (this->trueInXPercent(13)) {
        // Running
        this->running++;
        n *= (float) 3 / 4; // -25%
    } else if (this->trueInXPercent(26)) {
        // Throtting
        this->trotting++;
        n *=  (float) 7 / 8; // -12.5%
    }  

    if (overweightJockey) 
        n *= (float) 51 / 50; // +2% penalty
    else if (obeseJockey) 
        n *= (float) 21 / 20; // +.5% penality
    
    if (n < 1) {
        n = this->getStepSize();
    }

    return diceUnlim % n;   
}

bool RacingHorse::step() {
    int dice100 = (unsigned int)std::rand() % 100;
    unsigned int diceUnlim = (unsigned int)std::rand();

    int mod = this->calcStepMod(dice100, diceUnlim);

    return mod < 1 ? true : false;
}

void RacingHorse::tick() {
    //bool stepResult = this->step();
    this->position += this->step();
}

void RacingHorse::print(const Console& console) {
    std::string asterics(this->position, '*');
    console.out << asterics;//Walking Animation
}

void RacingHorse::reset() {
    this->position = 1;
}

void RacingHorse::prepare(const std::vector<std::reference_wrapper<RacingHorse>>& horses, 
const std::string& racename, 
unsigned int length){

    // Satisfy the compiling b**ch. Pretend to use the parameters
    // to prevent "unused parameter" errors :o)
    (void) horses;
    (void) racename;
    (void) length;

    int dice100 = (unsigned int)std::rand() % 100;

    if (dice100 % 10 >= 0 && dice100 % 10 <= 2) 
        this->overweightJockey = true;    
    
    else if (dice100 % 10 == 3 || dice100 % 10 == 4) 
        this->obeseJockey = true;

    if (dice100 > 40) {
        this->didPoo = true;//Free Step Boost when pood in preMatch
        this->position++; // poo horse one free, pog
    }
}

int RacingHorse::operator ==(RacingHorse that) const{
    if (this->getName() == that.getName())
        return 1;
    return 0;
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