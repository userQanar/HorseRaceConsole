#pragma once
#pragma once
#include "Bet.h"
//#include "RacerSet.h"
#include "RaceTrack.h"

class Player {
private:
	/** Name des Spielers */
	std::string name;

	/** In welcher Zeile soll das Objekt ausgegeben werden */
	int         line;

	/** Restvermoegen */
	int         money;
public:
	Player(std::string const& name, int line, int money);
	std::string const& getName() const;
	int getAvailableMoney() const;

	/** Ausgabe eines Spielers, name_ofs ist die fuer die Namensausgabe reservierte Breite */
	void print(Console& console, int name_ofs) const;

	/** Siehe print, zusaetzlich: Ausgabe einer Wette in der gleichen Zeile */
	void print(Console& console, int name_ofs, Bet const& bet) const;

	/** Gibt zurueck, ob das Restvermoegen positiv ist */
	bool canPlay() const;

	/** Erzeugt eine Wette, name_ofs siehe print */
	Bet makeBet(Console& console, int name_ofs,  immutableHorseList const& racers); // RacerSet const& racers

	/** Einloesen einer Wette */
	void resolveBet(Bet& bet, Racer const* winner);
private:
	/** Sicherstellung der Gueltigkeit der der Rueckgaben von selectAmountRacer */
	int saneSelectAmount(Console& console, int name_ofs, immutableHorseList const& racers);

	/** Sicherstellung der Gueltigkeit der Rueckgaben von selectRacer */
	Racer const* saneSelectRacer(Console& console, int name_ofs, immutableHorseList const& racers);

	/**
	 * Abstrakte Methode zur Bestimmung des Wetteinsatzes
	 */
	virtual int selectAmount(Console& console, immutableHorseList const& racers) = 0;

	/**
	 * Abstrakte Methode zur Auswahl des erwarteten Siegers
	 */
	virtual Racer const* selectRacer(Console& console, immutableHorseList const& racers) = 0;
};
