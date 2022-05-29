#include <cstdlib>
#include <chrono>
#include <thread>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>

#include "Console.h"
#include "Racer.h"
#include "RacingLane.h"
#include "RaceTrack.h"

using namespace std::chrono_literals;//fürn sleep_for i guess

int main()
{
    std::srand(std::time(0));
    Console myConsole;

    //Old Horses: Charles Wilhelm, Lady Shannon, Marcel Weawiz, Vinnie Wiesel, Lansagneausgangsprodukt, karensische Karen
    Racer       racer_A("markanter Mazura");
    Racer       racer_B("bezaubernde Beck");
    RagingBull  racer_C("kinetischer Kray");
    RagingBull  racer_D("hastiger Heinen");
    RagingBull  racer_E("stoischer Storz");
    RagingBull  racer_F("handelsreisender Hanner");
    RagingBull  racer_G("reimende Reimschuessel");
    FrillLizard racer_H("zielfuehrende Zimmermann");
    FrillLizard racer_I("uckermaerkischer Ussfeller");
    FrillLizard racer_J("babylonischer Bitterlich");
    FrillLizard racer_K("prekanter Preckel");
    RacingHorse racer_L("linguistische Loens-Niemann");
    RacingHorse racer_M("siegesbewusster Schmidt");
    RacingHorse racer_N("baggernder Bandel");
    RacingHorse racer_O("kickboxende Kirchgessner");
    //Own Favorite Horse: kinetischer Kray++ // +50 dkp wer nen Reim auf Reimschüssel findet
    //Fan Favorite Horse: stoischer Storz++ kinetischer Kray++ prekanter Preckel++

    RaceTrack raceTrack = RaceTrack();

    /*
    //Race 1
    const std::vector<std::reference_wrapper<Racer>> racingHorses = std::vector<std::reference_wrapper<Racer>>{
        std::ref(racer_A),
        std::ref(racer_B)
    };

    auto firstWinner = raceTrack.race("MINIRACE Requiem of Desolation ", myConsole, racingHorses, 50);
    myConsole.out << "Im Zweikampf hat das Pferd \"" << firstWinner.getName() << "\" gewonnen." << std::endl;
    std::this_thread::sleep_for(3s);
    myConsole.clearScreen();


    //Werbepause
    myConsole.out << "[AD-BREAK] Das grosse Rennen beginnt nach nur einem Spot! " << std::endl << std::endl;
    for (int i = 0; i < 20; i++) {
        myConsole.out << "Hallo, ich bin Marcel Davis, Leiter fuer Kundenzufridenheit bei 1&1.| " << "COCA COLA " << "YUMMY " << std::endl;
        std::this_thread::sleep_for(0.25s);
    }
    */

    //Race 2
    const std::vector<std::reference_wrapper<Racer>> racingHorses2{
        std::ref(racer_A),
        std::ref(racer_B),
        std::ref(racer_C),
        std::ref(racer_D),
        std::ref(racer_E),
        std::ref(racer_F),
        std::ref(racer_G),
        std::ref(racer_H),
        std::ref(racer_I),
        std::ref(racer_J),
        std::ref(racer_K),
        std::ref(racer_L),
        std::ref(racer_M),
        std::ref(racer_N),
        std::ref(racer_O) };
    //racingHorses = std::vector<std::reference_wrapper<Racer>>{ &pferd_A, & pferd_B, & pferd_C, & pferd_D, & pferd_E, & pferd_F, & pferd_G, & pferd_H, & pferd_I, & pferd_J, & pferd_K, & pferd_L, & pferd_M };

    auto secondWinner = raceTrack.race("BIGRACE this->\" hurts like bread in french\"", myConsole, racingHorses2, 79);
    myConsole.out << "Im grossen Wettkampf hat das Pferd \"" << secondWinner.getName() << "\" gewonnen." << std::endl << std::endl;


    // Buffs and Debuffs Counter 
    myConsole.out << "Das Pferd " << secondWinner.getName() << " nutzte heute seine Faehigkeit: " << std::endl << "Traben fuer \"" << secondWinner.trotting << "\"Sekunden, ";
    myConsole.out << "Rennen \"" << secondWinner.running << "\"Sekunden, ";
    myConsole.out << "Gallop \"" << secondWinner.galloping << "\"Sekunden." << std::endl;
    if (secondWinner.trotting >= 32)  myConsole.out << "Das Pferd trabte heute gerne " << std::endl;
    if (secondWinner.running >= 17)  myConsole.out << "Das Pferd rannte heute gerne " << std::endl;
    if (secondWinner.galloping >= 9)  myConsole.out << "Das Pferd gallopierte heute gerne " << std::endl;

    if (secondWinner.didPoo)
        myConsole.out << "Das Pferd " << secondWinner.getName() << " konnte sich heute vor dem Rennen \" erleichtern \" und damit einen Vorteil gewinnen." << std::endl;

    if (secondWinner.overweightJockey)
        myConsole.out << "Das Pferd " << secondWinner.getName() << " konnte sich heute trotz \" dickem Reiter \" als Gewinner durchsetzen." << std::endl << "+3 Damage to this->Wirbelsaeule" << std::endl;

    if (secondWinner.obeseJockey)
        myConsole.out << "Das Pferd " << secondWinner.getName() << " konnte sich heute trotz \" boes adipoesem Reiter \" als Gewinner durchsetzen." << std::endl << "+11 Damage to this->Wirbelsaeule" << std::endl;
    /*
    if (secondWinner == firstWinner)
        myConsole.out << "Das Pferd " << secondWinner.getName() << " zeigte sich heute mit seinem \" zweiten Sieg \" als wahrer Gewinner des Tages." << std::endl << std::endl;
    */
    return 0;
}
 