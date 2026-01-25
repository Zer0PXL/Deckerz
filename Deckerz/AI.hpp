#pragma once
#include "Card.hpp"
#include <vector>
#include <memory>

enum Difficulty
{
	NOAI,
	DUMB,
	SMART,
	UNFAIR
};

class AI
{
private:
	std::vector<std::shared_ptr<Card>> heartCards;
	std::vector<std::shared_ptr<Card>> spadeCards;
	std::vector<std::shared_ptr<Card>> diamondCards;
	std::vector<std::shared_ptr<Card>> clubCards;
	std::vector<std::shared_ptr<Card>> bestSuit;

	bool smoked = false;
	Difficulty difficulty = SMART;
public:
	void changeDifficulty(Difficulty difficulty);
	Suit determineBestSuit();
	Difficulty getDifficulty();
	void smokeBomb();
	bool isSmoked();

	std::vector<std::shared_ptr<Card>> getHearts();
	std::vector<std::shared_ptr<Card>> getSpades();
	std::vector<std::shared_ptr<Card>> getDiamonds();
	std::vector<std::shared_ptr<Card>> getClubs();
	std::vector<std::shared_ptr<Card>> getBest();
	void setHearts(std::vector<std::shared_ptr<Card>> newHearts);
	void setSpades(std::vector<std::shared_ptr<Card>> newSpades);
	void setDiamonds(std::vector<std::shared_ptr<Card>> newDiamonds);
	void setClubs(std::vector<std::shared_ptr<Card>> newClubs);
	void setBest(std::vector<std::shared_ptr<Card>> newBest);
};

