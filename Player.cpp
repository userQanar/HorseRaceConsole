#include "Player.h"

Player::Player(std::string const& name, int line, int money)
	: name(name)
	, line(line)
	, money(money)
{}

std::string const& Player::getName() const {
	return name;
}

bool Player::canPlay() const {
	return money > 0;
}

Bet Player::makeBet(Console& console, int name_ofs, immutableHorseList const& racers) {
	Racer const* expected_winner = saneSelectRacer(console, name_ofs, racers);
	int amount = saneSelectAmount(console, name_ofs, racers);
	money -= amount;
	Bet r(racers.size(), expected_winner, amount);
	print(console, name_ofs, r);
	return r;
}

int Player::getAvailableMoney() const {
	return money;
}

void Player::resolveBet(Bet& bet, Racer const* winner) {
	money += bet.resolve(winner);
}

void Player::print(Console& console, int name_ofs) const {
	console.moveTo(line, 1);
	console.clearLine();
	console.moveTo(line, 1);
	console.out << name << ": Konto: ";
	console.moveTo(line, name_ofs + 9);
	console.out << money;
}

void Player::print(Console& console, int name_ofs, Bet const& bet) const {
	print(console, name_ofs);
	console.moveTo(line, name_ofs + 15);
	console.out << " wettet ";
	bet.print(console);
}

Racer const* Player::saneSelectRacer(Console& console, int name_ofs, immutableHorseList const& racers) {
	while(true) {
		print(console, name_ofs);
		console.out << " Rennding (0...1) : ";
		Racer const* expected_winner = selectRacer(console, racers);
		//if(racers.has(expected_winner)) { ------------------------------> removed no Clue help 
			print(console, name_ofs);
			console.out << " Rennding: " << expected_winner->getName();
			return expected_winner;
		}
	}
//}---> wat is dis 
/*
 	bool has(Racer const* racer) const;
*/
/*
bool RacerSet::has(Racer const* racer) const {
	return racer == racer_a
		|| racer == racer_b
		;
}
*/

int Player::saneSelectAmount(Console& console, int name_ofs, immutableHorseList const& racers) {
	while(true) {
		print(console, name_ofs);
		console.out << " Einsatz (1..." << getAvailableMoney() << ") :";
		int amount = selectAmount(console, racers);
		if(amount > 0 && amount <= money) {
			print(console, name_ofs);
			console.out << " Einsatz: " << amount;
			return amount;
		}
	}
}