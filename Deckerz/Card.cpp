#include "Card.hpp"
#include "Debug.hpp"
#include "Chance.hpp"
#include "PlayState.hpp"
#include <iostream>
#include <string>

Card::Card(int r, Suit s, int id, Owner o, Ability a, Enhancement e) : rank(r), suit(s), id(id), owner(o), ability(a), enhancement(e) {}

void Card::print() const
{
	std::string ownerString = (owner == PLAYER ? "Player" : "AI");
	
	if (debugMode)
	{
		if (suit == HEARTS)
			std::cout << rank << " of Hearts (ID: " << id << ", Owner: " << ownerString << ", Ability: " << Debug::abilityToString(ability) << ", Enhancement: " << Debug::enhancementToString(enhancement) << ")" << std::endl;
		else if (suit == SPADES)
			std::cout << rank << " of Spades (ID: " << id << ", Owner: " << ownerString << ", Ability: " << Debug::abilityToString(ability) << ", Enhancement: " << Debug::enhancementToString(enhancement) << ")" << std::endl;
		else if (suit == DIAMONDS)
			std::cout << rank << " of Diamonds (ID: " << id << ", Owner: " << ownerString << ", Ability: " << Debug::abilityToString(ability) << ", Enhancement: " << Debug::enhancementToString(enhancement) << ")" << std::endl;
		else if (suit == CLUBS)
			std::cout << rank << " of Clubs (ID: " << id << ", Owner: " << ownerString << ", Ability: " << Debug::abilityToString(ability) << ", Enhancement: " << Debug::enhancementToString(enhancement) << ")" << std::endl;
		else if (suit == BLACKJOKER)
			std::cout << "Black Joker (ID: " << id << ", Owner: " << ownerString << ", Ability: " << Debug::abilityToString(ability) << ", Enhancement: " << Debug::enhancementToString(enhancement) << ")" << std::endl;
		else if (suit == REDJOKER)
			std::cout << "Red Joker (ID: " << id << ", Owner: " << ownerString << ", Ability: " << Debug::abilityToString(ability) << ", Enhancement: " << Debug::enhancementToString(enhancement) << ")" << std::endl;
		else
			std::cout << "Invalid card (ID: " << id << ")" << std::endl;
	}
	else
	{
		if (suit == HEARTS)
			std::cout << rank << " of Hearts (ID: " << id << ")" << std::endl;
		else if (suit == SPADES)
			std::cout << rank << " of Spades (ID: " << id << ")" << std::endl;
		else if (suit == DIAMONDS)
			std::cout << rank << " of Diamonds (ID: " << id << ")" << std::endl;
		else if (suit == CLUBS)
			std::cout << rank << " of Clubs (ID: " << id << ")" << std::endl;
		else if (suit == BLACKJOKER)
			std::cout << "Black Joker (ID: " << id << ")" << std::endl;
		else if (suit == REDJOKER)
			std::cout << "Red Joker (ID: " << id << ")" << std::endl;
		else
			std::cout << "Invalid card (ID: " << id << ")" << std::endl;
	}
}

int Card::getSuit() const
{
	return suit;
}

void Card::setSuit(Suit s)
{
	suit = s;
}

int Card::getRank() const
{
	return rank;
}

void Card::setRank(int r)
{
	rank = r;
}

int Card::getID() const
{
	return id;
}

Owner Card::getOwner() const
{
	return owner;
}

void Card::setOwner(Owner o)
{
	owner = o;
}

bool Card::isPlayable(std::shared_ptr<Card> cardToPlay, std::shared_ptr<Card> pileCard)
{
	Debug::log("[Card.cpp] Checking if these two cards are playable:");
	cardToPlay->print();
	pileCard->print();
	
	if (cardToPlay->getRank() == pileCard->getRank()) Debug::log("[Card.hpp] That card has the same rank as the card on the pile!");
	else if (cardToPlay->getSuit() == pileCard->getSuit()) Debug::log("[Card.hpp] That card has the same suit as the card on the pile!");
	else if (cardToPlay->getRank() == -1) Debug::log("[Card.hpp] That card is a Joker!");
	else if (pileCard->getRank() == -1) Debug::log("[Card.hpp] The pile card is a Joker!");
	else Debug::log("[Card.hpp] X - Unplayable.");
	
	if (cardToPlay->getRank() == pileCard->getRank() || // IF the card you're about to play has the same rank
		cardToPlay->getSuit() == pileCard->getSuit() || // OR the cards have the same suit
		cardToPlay->getRank() == -1 || // OR the card to play is a Joker
		pileCard->getRank() == -1) // OR the card on the pile is a Joker
	{
		return true; // Then, yeah, it's playable :thumbs up:
	}
	else return false; // Otherwise, you can't play random cards :sad:
}

Ability Card::getAbility() const
{
	return ability;
}

void Card::setAbility(Ability a)
{
	ability = a;
}

Suit Card::intToSuit(int interger)
{
	switch (interger)
	{
	case 0:
		return HEARTS;
		break;
	case 1:
		return SPADES;
		break;
	case 2:
		return DIAMONDS;
		break;
	case 3:
		return CLUBS;
		break;
	default:
		std::cout << "X - Invalid interger for intToSuit()\n";
		return HEARTS;
		break;
	}
}

Enhancement Card::getEnhancement()
{
	return enhancement;
}

void Card::setEnhancement(Enhancement e)
{
	enhancement = e;
}

/*void Card::actEnhancement(PlayState& ps)
{
	int randomCard;
	
	switch (enhancement)
	{
		case EXTRAEN:
			ps.score += 10;
			std::cout << "+ 10!\n";
			break;
		
		case STICKY:
			randomCard = Chance::chance(0, ps.getPHand().getSize());
			ps.getPHand().playCards({ps.getPHand().getHand()[randomCard]}, gs);
	}	
}
*/
void Card::setID(int newID)
{
	id = newID;
}

void Card::resetAbility()
{
	if (rank == 1)
	{
		ability = COLOR;
	}
	if (rank == 2 || rank == 3)
	{
		ability = DRAWABILITY;
	}
	else if (rank == 4)
	{
		ability = SKIP;
	}
}