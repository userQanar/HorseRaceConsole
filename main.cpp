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
    RacingHorse pferd_A = RacingHorse(std::string("markanter Mazura"));
    RacingHorse pferd_B = RacingHorse(std::string("bezaubernde Beck"));
    RacingHorse pferd_C = RacingHorse(std::string("kinetischer Kray"));
    RacingHorse pferd_D = RacingHorse(std::string("hastiger Heinen"));
    RacingHorse pferd_E = RacingHorse(std::string("stoischer Storz"));
    RacingHorse pferd_F = RacingHorse(std::string("handelsreisender Hanner"));
    RacingHorse pferd_G = RacingHorse(std::string("reimende Reimschuessel")); 
    RacingHorse pferd_H = RacingHorse(std::string("zielfuehrende Zimmermann"));
    RacingHorse pferd_I = RacingHorse(std::string("uckermaerkischer Ussfeller"));
    RacingHorse pferd_J = RacingHorse(std::string("babylonischer Bitterlich"));
    RacingHorse pferd_K = RacingHorse(std::string("prekanter Preckel"));
    RacingHorse pferd_L = RacingHorse(std::string("linguistische Loens-Niemann"));
    RacingHorse pferd_M = RacingHorse(std::string("siegesbewusster Schmidt"));
    //Own Favorite Horse: kinetischer Kray++ // +50 dkp wer nen Reim auf Reimschüssel findet
    //Fan Favorite Horse: stoischer Storz++ kinetischer Kray++ prekanter Preckel++

    RaceTrack raceTrack = RaceTrack();
    RacingHorse* winnerHorse;

    //Race 1
    winnerHorse = raceTrack.race("MINIRACE Requiem of Desolation ", myConsole, std::vector<RacingHorse*>{
        &pferd_A,
        &pferd_B
    }, 50);
    myConsole.out << "Im Zweikampf hat das Pferd \"" << winnerHorse->getName() << "\" gewonnen." << std::endl;
    std::this_thread::sleep_for(3s);
    myConsole.clearScreen();
    winnerHorse->winnerFirstGame = true;

    //Werbepause /**/
    myConsole.out << "[AD-BREAK] Das grosse Rennen beginnt nach nur einem Spot! " << std::endl << std::endl;
    for (int i = 0; i < 20; i++) {
        myConsole.out << "Vagisil bei Scheidenpilz | " << "COCA COLA " << "YUMMY " << std::endl;
        std::this_thread::sleep_for(.25s);
    }/**/

    //Race 2
    winnerHorse = raceTrack.race("BIGRACE this->\" hurts like bread in french\"", myConsole, std::vector<RacingHorse*>{
        &pferd_A, & pferd_B, & pferd_C, & pferd_D, & pferd_E, & pferd_F, & pferd_G, & pferd_H, & pferd_I, & pferd_J, & pferd_K, & pferd_L, & pferd_M }, 79);
    myConsole.out << "Im grossen Wettkampf hat das Pferd \"" << winnerHorse->getName() << "\" gewonnen." << std::endl << std::endl;

    // Buffs and Debuffs Counter
    myConsole.out << "Das Pferd " << winnerHorse->getName() << " nutzte heute seine Faehigkeit: " << std::endl << "Traben fuer \"" << winnerHorse->trotting << "\"Sekunden, ";
    myConsole.out << "Rennen \"" << winnerHorse->running << "\"Sekunden, ";
    myConsole.out << "Gallop \"" << winnerHorse->galloping << "\"Sekunden." << std::endl;
    if (winnerHorse->trotting >= 32) { myConsole.out << "Das Pferd trabte heute gerne " << std::endl; }
    if (winnerHorse->running >= 17) { myConsole.out << "Das Pferd rannte heute gerne " << std::endl; }
    if (winnerHorse->galloping >= 9) { myConsole.out << "Das Pferd gallopierte heute gerne " << std::endl; }
    
    if (winnerHorse->didPoo) {
        myConsole.out << "Das Pferd " << winnerHorse->getName() << " konnte sich heute vor dem Rennen \" erleichtern \" und damit einen Vorteil gewinnen." << std::endl;}
    if (winnerHorse->overweightJockey) {
        myConsole.out << "Das Pferd " << winnerHorse->getName() << " konnte sich heute trotz \" dickem Reiter \" als Gewinner durchsetzen." << std::endl << "+3 Damage to this->Wirbelsaeule" << std::endl;}
    if (winnerHorse->obeseJockey) {
        myConsole.out << "Das Pferd " << winnerHorse->getName() << " konnte sich heute trotz \" boes adipoesem Reiter \" als Gewinner durchsetzen." << std::endl << "+11 Damage to this->Wirbelsaeule" << std::endl;}
    if (winnerHorse->winnerFirstGame) {
        myConsole.out << "Das Pferd " << winnerHorse->getName() << " zeigte sich heute mit seinem \" zweiten Sieg \" als wahrer Gewinner des Tages." << std::endl << std::endl;}

    return 0;
}
/*
To quote Hamlet
        act III
      scene iii
        line 87
           - no
*///Quelle: © booksididnt 2022, Tshirt Print 