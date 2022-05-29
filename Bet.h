#pragma once
#include "Racer.h"

/**
 * Die Klasse Bet modelliert eine Wette.
 */
class Bet {
	/** Verhaeltnis von Gewinn zu Einsatz */
	double       ratio;

	/** Auf welchen Racer wurde gesetzt? */
	Racer const* expected_winner;

	/** Wieviel wurde gesetzt? */
	int          amount;
public:
	Bet(double ratio, Racer const* expected_winner, int amount);

	/**
	 * Einloesen einer Wette:
	 *  - Gewinn wird zurueck gegeben
	 *  - amount wird auf 0 gesetzt
	 */
	int resolve(Racer const* winner);

	/**
	 * Rueckgabe des Betrags, der im Falle eines
	 * Gewinns ausgeschuettet werden wuerde
	 */
	int onWin() const;

	/**
	 * Ausgabe
	 */
	void print(Console& console) const;
};
