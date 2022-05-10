#include <cstdlib>
#include <chrono>
#include <thread>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>

#include "Console.h"
#include "RacingHorse.h"
#include "RacingLane.h"
#include "RaceTrack.h"

using namespace std::chrono_literals;//fürn sleep_for i guess

int main()
{
    std::srand(std::time(0));
    Console myConsole;

    //Old Horses: Charles Wilhelm, Lady Shannon, Marcel Weawiz, Vinnie Wiesel, Lansagneausgangsprodukt, karensische Karen
    RacingHorse pferd_A("markanter Mazura");
    RacingHorse pferd_B("bezaubernde Beck");
    RacingHorse pferd_C("kinetischer Kray");
    RacingHorse pferd_D("hastiger Heinen");
    RacingHorse pferd_E("stoischer Storz");
    RacingHorse pferd_F("handelsreisender Hanner");
    RacingHorse pferd_G("reimende Reimschuessel");
    RacingHorse pferd_H("zielfuehrende Zimmermann");
    RacingHorse pferd_I("uckermaerkischer Ussfeller");
    RacingHorse pferd_J("babylonischer Bitterlich");
    RacingHorse pferd_K("prekanter Preckel");
    RacingHorse pferd_L("linguistische Loens-Niemann");
    RacingHorse pferd_M("siegesbewusster Schmidt");
    RacingHorse pferd_N("baggernder Bandel");
    RacingHorse pferd_O("kickboxende Kirchgessner");
    //Own Favorite Horse: kinetischer Kray++ // +50 dkp wer nen Reim auf Reimschüssel findet
    //Fan Favorite Horse: stoischer Storz++ kinetischer Kray++ prekanter Preckel++

    RaceTrack raceTrack = RaceTrack();

    //Race 1
    const std::vector<std::reference_wrapper<RacingHorse>> racingHorses = std::vector<std::reference_wrapper<RacingHorse>>{
        std::ref(pferd_A),
        std::ref(pferd_B)
    };

    auto firstWinner = raceTrack.race("MINIRACE Requiem of Desolation ", myConsole, racingHorses, 50);
    myConsole.out << "Im Zweikampf hat das Pferd \"" << firstWinner.getName() << "\" gewonnen." << std::endl;
    std::this_thread::sleep_for(3s);
    myConsole.clearScreen();


    //Werbepause
    myConsole.out << "[AD-BREAK] Das grosse Rennen beginnt nach nur einem Spot! " << std::endl << std::endl;
    for (int i = 0; i < 20; i++) {
        myConsole.out << "Vagisil bei Scheidenpilz | " << "COCA COLA " << "YUMMY " << std::endl;
        std::this_thread::sleep_for(0.25s);
    }

    //Race 2
    const std::vector<std::reference_wrapper<RacingHorse>> racingHorses2{
        std::ref(pferd_A),
        std::ref(pferd_B),
        std::ref(pferd_C),
        std::ref(pferd_D),
        std::ref(pferd_E),
        std::ref(pferd_F),
        std::ref(pferd_G),
        std::ref(pferd_H),
        std::ref(pferd_I),
        std::ref(pferd_J),
        std::ref(pferd_K),
        std::ref(pferd_L),
        std::ref(pferd_M),
        std::ref(pferd_N),
        std::ref(pferd_O) };
    //racingHorses = std::vector<std::reference_wrapper<RacingHorse>>{ &pferd_A, & pferd_B, & pferd_C, & pferd_D, & pferd_E, & pferd_F, & pferd_G, & pferd_H, & pferd_I, & pferd_J, & pferd_K, & pferd_L, & pferd_M };

    auto secondWinner = raceTrack.race("BIGRACE this->\" hurts like bread in french\"", myConsole, racingHorses2, 79);
    myConsole.out << "Im grossen Wettkampf hat das Pferd \"" << secondWinner.getName() << "\" gewonnen." << std::endl << std::endl;
/*
 To quote Hamlet
         act III
       scene iii
        line 87
           - no
*/   //Quelle:  booksididnt 2022, Tshirt Print  

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

    if (secondWinner == firstWinner)
        myConsole.out << "Das Pferd " << secondWinner.getName() << " zeigte sich heute mit seinem \" zweiten Sieg \" als wahrer Gewinner des Tages." << std::endl << std::endl;

    return 0;
}
 