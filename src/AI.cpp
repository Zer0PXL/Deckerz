#include "AI.hpp"
#include "Debug.hpp"
#include <string>

Suit AI::determineBestSuit()
{
	// Determine the bestSuit
	if (heartCards.size() >= spadeCards.size() &&
		heartCards.size() >= diamondCards.size() &&
		heartCards.size() >= clubCards.size())
	{
		Debug::log("[AI.cpp] The best suit is Hearts with ", std::to_string(heartCards.size()), " cards.");
		return HEARTS;
	}
	else if (spadeCards.size() >= heartCards.size() &&
		spadeCards.size() >= diamondCards.size() &&
		spadeCards.size() >= clubCards.size())
	{
		Debug::log("[AI.cpp] The best suit is Spades with ", std::to_string(spadeCards.size()), " cards.");
		return SPADES;
	}
	else if (diamondCards.size() >= heartCards.size() &&
		diamondCards.size() >= spadeCards.size() &&
		diamondCards.size() >= clubCards.size())
	{
		Debug::log("[AI.cpp] The best suit is Diamonds with ", std::to_string(diamondCards.size()), " cards.");
		return DIAMONDS;
	}
	else if (clubCards.size() >= heartCards.size() &&
		clubCards.size() >= spadeCards.size() &&
		clubCards.size() >= diamondCards.size())
	{
		Debug::log("[AI.cpp] The best suit is Clubs with ", std::to_string(clubCards.size()), " cards.");
		return CLUBS;
	}
	else
	{
		Debug::log("[AI.cpp] The AI doesn't have any playable cards.");
		return HEARTS;
	}
}

void AI::changeDifficulty(Difficulty newDifficulty)
{
	difficulty = newDifficulty;
}

Difficulty AI::getDifficulty()
{
	return difficulty;
}

void AI::smokeBomb()
{
	if (!smoked) smoked = true;
	else smoked = false;
}

bool AI::isSmoked()
{
	return smoked;
}

std::vector<std::shared_ptr<Card>> AI::getHearts()
{
	return heartCards;
}

std::vector<std::shared_ptr<Card>> AI::getSpades()
{
	return spadeCards;
}

std::vector<std::shared_ptr<Card>> AI::getDiamonds()
{
	return diamondCards;
}

std::vector<std::shared_ptr<Card>> AI::getClubs()
{
	return clubCards;
}

std::vector<std::shared_ptr<Card>> AI::getBest()
{
	return bestSuit;
}

void AI::setHearts(std::vector<std::shared_ptr<Card>> newHearts)
{
	heartCards = std::move(newHearts);
}

void AI::setSpades(std::vector<std::shared_ptr<Card>> newSpades)
{
	spadeCards = std::move(newSpades);
}

void AI::setDiamonds(std::vector<std::shared_ptr<Card>> newDiamonds)
{
	diamondCards = std::move(newDiamonds);
}

void AI::setClubs(std::vector<std::shared_ptr<Card>> newClubs)
{
	clubCards = std::move(newClubs);
}

void AI::setBest(std::vector<std::shared_ptr<Card>> newBest)
{
	bestSuit = std::move(newBest);
}