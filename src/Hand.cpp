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

std::vector<std::shared_ptr<Card>> mergeSort(int p, int q, std::vector<std::shared_ptr<Card>> &hand)
{
	int mij = (p+q)/2, i = 0, j = 0;
	std::vector<std::shared_ptr<Card>> dH1, dH2, finalHand;

	if (p==q)
	{
		dH1.push_back(hand[p]);
		return dH1;
	}
	else
	{
		dH1 = mergeSort(p, mij, hand);
		dH2 = mergeSort(mij+1, q, hand);

		while (i < dH1.size() && j < dH2.size())
		{
			if (dH1[i]->getRank() < dH2[j]->getRank())
			{
				finalHand.push_back(dH1[i]);
				i++;
			}
			else
			{
				finalHand.push_back(dH2[j]);
				j++;
			}
		}

		if (i < dH1.size()) for (; i < dH1.size(); i++) finalHand.push_back(dH1[i]);
		if (j < dH2.size()) for (; j < dH2.size(); j++) finalHand.push_back(dH2[j]);

		return finalHand;
	}
}

std::vector<std::shared_ptr<Card>> Hand::sortHand(std::vector<std::shared_ptr<Card>> unsorted)
{
	std::vector<std::shared_ptr<Card>> sorted, hearts, spades, clubs, diamonds, blackJokers, redJokers;

	for (auto card : unsorted)
	{
		switch (card->getSuit())
		{
			case HEARTS:
				hearts.push_back(card);
				break;
			case SPADES:
				spades.push_back(card);
				break;
			case CLUBS:
				clubs.push_back(card);
				break;
			case DIAMONDS:
				diamonds.push_back(card);
				break;
			case REDJOKER:
				redJokers.push_back(card);
				break;
			case BLACKJOKER:
				blackJokers.push_back(card);
				break;
			default:
				Debug::log ("[Hand.cpp] Card with invalid suit found while sorting hand!");
				hearts.push_back(card);
				break;
		}
	}

	if (!hearts.empty())
	{
		hearts = mergeSort(0, hearts.size()-1, hearts);
		sorted.insert(sorted.end(), hearts.begin(), hearts.end());
	}
	if (!spades.empty())
	{
		spades = mergeSort(0, spades.size()-1, spades);
		sorted.insert(sorted.end(), spades.begin(), spades.end());
	}
	if (!clubs.empty())
	{
		clubs = mergeSort(0, clubs.size()-1, clubs);
		sorted.insert(sorted.end(), clubs.begin(), clubs.end());
	}
	if (!diamonds.empty())
	{
		diamonds = mergeSort(0, diamonds.size()-1, diamonds);
		sorted.insert(sorted.end(), diamonds.begin(), diamonds.end());
	}
	if (!blackJokers.empty())
	{
		sorted.insert(sorted.end(), blackJokers.begin(), blackJokers.end());
	}
	if (!redJokers.empty())
	{
		sorted.insert(sorted.end(), redJokers.begin(), redJokers.end());
	}

	return sorted;
}