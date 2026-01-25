#include "Hand.hpp"
#include "Card.hpp"
#include "Debug.hpp"
#include "PlayState.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <memory>

void Hand::addCard(std::shared_ptr<Card> card)
{
	hand.push_back(card);
}

void Hand::removeCard(std::shared_ptr<Card> card)
{
	int toDelete = -1;

	for (int i = 0; i < hand.size(); i++)
	{
		if (card->getID() == hand[i]->getID())
		{
			toDelete = i;
			break;
		}
	}
	if (toDelete == -1)
	{
		Debug::log("[Hand.cpp] X - Tried to delete a card that isn't in hand!");
		return;
	}

	hand.erase(hand.begin() + toDelete);
}

int Hand::getSize()
{
	return hand.size();
}

std::vector<std::shared_ptr<Card>>& Hand::getHand()
{
	return hand;
}