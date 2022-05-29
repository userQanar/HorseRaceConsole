#include <cmath>
#include "Bet.h"

Bet::Bet(double ratio, Racer const* expected_winner, int amount)
	: ratio(ratio)
	, expected_winner(expected_winner)
	, amount(amount)
{}

int Bet::resolve(Racer const* winner) {
	int r = expected_winner == winner
		? onWin()
		: 0
		;
	amount = 0;
	return r;
}

int Bet::onWin() const {
	return static_cast<int>(std::round(ratio * amount));
}

void Bet::print(Console& console) const {
	console.out << amount << " auf " << expected_winner->getName();
}
