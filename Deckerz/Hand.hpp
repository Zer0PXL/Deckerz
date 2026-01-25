#pragma once
#include <iostream>
#include <vector>
#include "Card.hpp"
#include "Deck.hpp"
#include <memory>

class Hand
{
private:
	std::vector<std::shared_ptr<Card>> hand;
public:
	void addCard(std::shared_ptr<Card> card);
	void removeCard(std::shared_ptr<Card> card);
	int getSize();
	std::vector<std::shared_ptr<Card>>& getHand();
};

