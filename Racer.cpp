#include "Racer.h"
#include "Console.h"

Racer::Racer(const std::string& name) :
    name(name),
    jockey(std::nullopt),
    position(1) // minus coordinates crash loop
{}

Racer::Racer(const std::string& name, const RacingJockey& jockey) :
    name(name),
    jockey(jockey),
    position(1) // minus coordinates crash loop
{}

Racer::~Racer() {
    this->name.clear();
    if (this->jockey.has_value())
        this->jockey.reset();
}

std::string Racer::getName() const {
    return this->name;
}

unsigned int Racer::getPosition() {
    return this->position;
}

unsigned int Racer::getStepSize() {
    return Racer::stepSize;
}

bool  Racer::trueInXPercent(unsigned int percentage) {
    auto dice100 = (unsigned int)std::rand() % 100;
    return dice100+1 <= percentage;
}

int Racer::calcStepMod(int dice100, unsigned int diceUnlim) {
    unsigned int n = this->getStepSize();
    //unsigned int n = (double) this->getStepSize();

    // If the Horse has no jockey, it might either be faster, equally fast, or slower
    // Depending if horse is insane or epic
    // Values ranging between 49, 50, 51 -> Either -0.2%, no change, or +0.2%
    if (!this->jockey.has_value()) {
        float factor = ((float)(dice100 % 3) + 49.0f) / 50.0f;
        n *= factor;
    }
    else {
        JockeyWeight weight = this->jockey->getWeightCategory();
        if (weight == THIN)
            n *= 3.0f / 4.0f;
        if (weight == THICC)
            n *= 4.0f / 3.0f;
        if (weight == OBESE)
            n *= 5.0f / 3.0f;
    }

    //Movement Abilitys
    if (this->trueInXPercent(7)) {
        this->gallopingBool = true;
        n *= (float)1 / 2; // -50%
    }
    else if (this->trueInXPercent(13)) {
        this->runningBool = true;
        n *= (float)3 / 4; // -25%
    }
    else if (this->trueInXPercent(26)) {
        this->trottingBool = true;
        n *= (float)7 / 8; // -12.5%
    }

    if (overweightJockey)
        n *= (float)51 / 50; // +2% penalty
    else if (obeseJockey)
        n *= (float)21 / 20; // +5% penality

    if (n < 1) {
        n = this->getStepSize();
    }

    if (this->trottingBool || this->runningBool || this->gallopingBool) {
        if (this->gallopingBool && diceUnlim % n < 1)this->galloping++;
        this->gallopingBool = false;
        if (this->runningBool && diceUnlim % n < 1)this->running++;
        this->runningBool = false;
        if (this->trottingBool && diceUnlim % n < 1)this->trotting++;
        this->trottingBool = false;
    }

    return diceUnlim % n;
}

int Racer::step() {
    int dice100 = (unsigned int)std::rand() % 100;
    unsigned int diceUnlim = (unsigned int)std::rand();

    int mod = this->calcStepMod(dice100, diceUnlim);

    return mod < 1 ? 1 : 0;
}
//Die Methode step soll zufällige Werte aus der Menge{ -1, 0, 1, 2 } zurückgeben können.
int FrillLizard::step() {

    if (this->getPosition() < 1) return 1;
    int dice100 = (unsigned int)std::rand() % 100;
    unsigned int diceUnlim = (unsigned int)std::rand();

    int mod = this->calcStepMod(dice100, diceUnlim);

    int dice4 = (((unsigned int)std::rand() % 4) - 1);

    return mod < 1 ? dice4 : 0;
}

int RagingBull::step() {

    if (this->getPosition() < 5) return 5;
    int dice100 = (unsigned int)std::rand() % 100;
    unsigned int diceUnlim = (unsigned int)std::rand();

    int mod = this->calcStepMod(dice100, diceUnlim);


    int dice9 = (((unsigned int)std::rand() % 10) - 4);
    return mod < 1 ? dice9 : 0;
}

void Racer::tick() {
    //bool stepResult = this->step();
    this->position += this->step();
}

void Racer::print(const Console& console) {
    std::string asterics(this->position, '*');
    console.out << asterics;//Walking Animation
}

void FrillLizard::print(const Console& console) {
    std::string asterics(this->position, 'x');
    console.out << asterics;//Walking Animation
}

void RagingBull::print(const Console& console) {
    std::string asterics(this->position, '>');
    console.out << asterics;//Walking Animation
}

void Racer::reset() {
    this->position = 1; // minus coordinates crash loop
}

void Racer::prepare(const std::vector<std::reference_wrapper<Racer>>& horses,
    const std::string& racename,
    unsigned int length) {

    // Satisfy the compiling b**ch. Pretend to use the parameters
    // to prevent "unused parameter" errors :o)
    (void)horses;
    (void)racename;
    (void)length;

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

int Racer::operator ==(Racer that) const {
    if (this->getName() == that.getName())
        return 1;
    return 0;
}

/*//Savegame normal Step\\
bool Racer::step() {
   unsigned int n = Racer::getStepSize();
   int mod = (unsigned int)std::rand() % n;
   return mod < 1 ? true : false;
}*/


/* @Brief 
Zwei Drittel der Männer (67 %) und die Hälfte der Frauen (53 %) in Deutschland sind übergewichtig.      // gerundet ~50% für Horse->weightModifier Frauen wiegen weniger in kg
Ein Viertel der Erwachsenen (23 % der Männer und 24 % der Frauen) ist stark übergewichtig (adipös).     // gerundet ~20% für Horse->weightModifier Frauen wiegen weniger in kg

Übergewicht und Adipositas sind Mitursache für viele Beschwerden und können die Entwicklung chronischer Krankheiten begünstigen.
Aufgrund der steigenden Prävalenz und den damit verbundenen Folgeerkrankungen entstehen beträchtliche Kosten für das Gesundheits- und Sozialsystem.
Übergewicht und Adipositas sind daher Themen von hoher Public-Health-Relevanz.

Das Robert Koch-Institut erhebt im Rahmen des Gesundheitsmonitorings regelmäßig Daten zu Übergewicht und Adipositas.
In den Auswertungen des RKI geht es um mehr als nur um die Prävalenz:
Zusammenhänge zu anderen Lebensparametern, wie beispielsweise Bewegung, Ernährungsverhalten oder sozialer Status werden erforscht.
Quelle: © Robert Koch-Institut 2014, Studie DEGS1, Erhebung 2008–2011

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
 if dickerReiter -> 2% Chance den else normaler Step zu verkacken 5% bei bös adipös <-done
 if winnerFirstGame -> 9,09% boost to regularStep <- done
*/ 