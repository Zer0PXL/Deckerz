#include <random>
#include <iostream>
#include "PlayState.hpp"
#include "Hand.hpp"
#include "Chance.hpp"
#include "Debug.hpp"


PlayState::PlayState() : playerDeck(PLAYER), aiDeck(OWNERAI), gameOver(NOTOVER), score(0)
{
	Debug::log("[PlayState.cpp] Starting PlayState...");

	// Shuffle decks
	playerDeck.shuffle();
	aiDeck.shuffle();

	// Each player draws 5 cards
	if (playerDeck.getSize() < 1)
	{
		gameOver = NOPLAYERDECK;
	}
	for (int i = 1; i <= 5; i++)
	{
		playerHand.addCard(playerDeck.draw());
		aiHand.addCard(aiDeck.draw());
	}

	// Flip a coin to determine first-goer
	if (Chance::chance(1, 2) == 1) turn = PLAYERTURN;
	else turn = AITURN;

	// Draw a card to the pile
	Debug::log("[PlayState.cpp] Drawing a card from the loser's deck...");
	if (turn == PLAYERTURN) pile.addCard(aiDeck.draw());
	else pile.addCard(playerDeck.draw());
}

// Deprecated
// Turn PlayState::playTurn(Turn& turn)
/*{
	if (turn) Debug::log("[PlayState.cpp] It's the AI's turn");
	else Debug::log("[PlayState.cpp] It's the Player's turn");

	//std::vector<Card>& hand = (turn == PLAYERTURN) ? pHand.getHand() : aHand.getHand();
	const std::vector<std::shared_ptr<Card>>& hand = aHand.getHand();
	std::vector<std::shared_ptr<Card>> playable;
	std::vector<std::shared_ptr<Card>> multiPlayable;
	std::shared_ptr<Card> topCard = pile.getCard();

	// Check for playable cards
	for (int i = 0; i < hand.size(); i++)
	{
		if (topCard->getRank() == -1) playable.push_back(hand[i]); // When a Joker is down, you can play whatever you want
		if (topCard->getRank() == hand[i]->getRank()) playable.push_back(hand[i]); // By rank
		if (topCard->getSuit() == hand[i]->getSuit()) playable.push_back(hand[i]); // By suit
		if (hand[i]->getRank() == -1) playable.push_back(hand[i]); // Jokers are always playable
	}

	// Old debugging AI
	if (turn == PLAYERTURN)
	{
		// Old Player-AI debugging thing
		if (topCard.getRank() == -1)
		{
			pile.addCard(pHand.playCard(playable[0])); // If there's a Joker down, though, you can't play your whole goddamn hand...
		}
		else if (playable.size() < 1)
		{
			// Check for deck
			if (pDeck.getSize() == 0)
			{
				gameOver = NOPLAYERDECK;
			}
			else pHand.addCard(pDeck.draw());
		}
		else if (playable.size() == 1) pile.addCard(pHand.playCard(playable[0]));
		else if (playable.size() > 1)
		{
			int baseRank = playable[0].getRank();
			for (int i = 0; i < playable.size(); i++)
			{
				if (playable[i].getRank() == baseRank) multiPlayable.push_back(playable[i]);
			}
			pile.addMultiCard(pHand.playMultiCard(multiPlayable));
		}

		return AITURN;
	}
	else
	{
		std::shared_ptr<Card> temporaryCard = std::make_shared<Card>(0, 0, 0, NONE, BASIC);
		std::vector<std::shared_ptr<Card>> temporaryCards;

		if (playable.size() < 1)
		{
			// Check for deck
			if (aDeck.getSize() == 0)
			{
				gameOver = NOAIDECK;
			}
			else
			{
				aHand.addCard(aDeck.draw());
				turn = PLAYERTURN;
			}
		}
		else if (playable.size() == 1) 
		{
			temporaryCard = playable[0];
			pile.addCard(aHand.playCard(playable[0]));
            turn = temporaryCard->actAbility(pHand, aHand, pDeck, aDeck, pile, turn);
		}
		else if (playable.size() > 1) 
		{
			for (int i = 0; i < playable.size(); i++)
			{
				if (playable[0]->getRank() == playable[i]->getRank())
				{
					temporaryCards.push_back(playable[i]);
				}
			}
			pile.addMultiCard(aHand.playMultiCard(playable));
			for (int i = 0; i < temporaryCards.size(); i++)
			{
				turn = temporaryCards[i]->actAbility(pHand, aHand, pDeck, aDeck, pile, turn);
			}
		}

		Debug::log("[PlayState.cpp] AI's turn is over.");

		return turn;
	}
}*/

GameOver PlayState::isGameOver()
{	
	if (gameOver == NOTOVER)
	{
		if (playerHand.getHand().size() == 0)
		{
			return PLAYERWIN;
		}
		else if (aiHand.getHand().size() == 0)
		{
			return AIWIN;
		}
		else
		{
			return NOTOVER;
		}
	}
	else return gameOver;
}

void PlayState::endRound()
{
	int kings = 0;
	int jokers = 0;
	
	// Shuffle the cards in hand back into their respective decks
	for (int i = playerHand.getSize() - 1; i >= 0; i--)
	{
		playerDeck.addCard(playerHand.getHand()[i]);
	}
	playerHand.getHand().clear();
	
	for (int i = aiHand.getSize() - 1; i >= 0; i--)
	{
		aiDeck.addCard(aiHand.getHand()[i]);
	}
	aiHand.getHand().clear();

	// Checking for bonuses...
	for (int i = 0; i < pile.getPile().size(); i++)
	{
		if (pile.getPile()[i]->getOwner() == PLAYER)
		{
			if (pile.getPile()[i]->getRank() == 13) kings++;
			if (pile.getPile()[i]->getRank() == -1) jokers++;
		}
	}
	if (kings >= 4) bonuses.royalty = true;
	if (jokers >= 2) bonuses.jokester = true;

	for (int i = 0; i < pile.getPile().size(); i++)
	{
		if (pile.getPile()[i]->getOwner() == PLAYER) playerDeck.addCard(pile.getPile()[i]);
		else if (pile.getPile()[i]->getOwner() == OWNERAI) aiDeck.addCard(pile.getPile()[i]);
	}

	// Clearing the pile and adding the cards back in their respective decks (check function)
	pile.clearPile(playerDeck, aiDeck);
}

void PlayState::switchTurn()
{
	if (turn == PLAYERTURN) turn = AITURN;
	else turn = PLAYERTURN;
}

void PlayState::calculateBonuses()
{
	std::cout << "=====================BREAKDOWN=====================" << std::endl;
	
	if (variables.draws > 0)
	{
		score += variables.draws * 10;
		std::cout << "+ " << variables.draws * 10 << " - Drawn cards\n";
	}
	if (variables.skips > 0)
	{
		score += variables.skips * 50;
		std::cout << "+ " << variables.skips * 50 << " - Skip cards\n";
	}
	if (variables.attacks > 0)
	{
		score += variables.attacks * 10;
		std::cout << "+ " << variables.attacks * 10 << " - Attack cards\n";
	}

	if (gameOver == PLAYERWIN || gameOver == NOAIDECK)
	{
		score += 100;
		std::cout << "+ 100 - Won!\n";
	}

	if (bonuses.comeback)
	{
		score += 75;
		std::cout << "+ 75 - Comeback!\n";
	}
	if (bonuses.jokester)
	{
		score += 100;
		std::cout << "+ 100 - Jokester!\n";
	}
	if (bonuses.royalty)
	{
		score += 200;
		std::cout << "+ 200 - Royalty!\n";
	}
	if (bonuses.noDraw)
	{
		score += 150;
		std::cout << "+ 150 - No Deck Needed!\n";
	}
	if (bonuses.oneManShow)
	{
		score += 200;
		std::cout << "+ 200 - One Man Show!?\n";
	}
	if (bonuses.oneShotWonder)
	{
		score += 300;
		std::cout << "+ 300 - ONE SHOT WONDER!?\n";
	}
	if (!bonuses.comeback &&
		!bonuses.jokester &&
		!bonuses.royalty &&
		!bonuses.noDraw &&
		!bonuses.oneManShow &&
		!bonuses.oneShotWonder)
	{
		std::cout << "No bonuses :(\n";
	}

	std::cout << "===================================================" << std::endl;
}

void PlayState::resetBonuses() {
	bonuses = Bonuses();
	variables = Variables();
}

Deck& PlayState::getPDeck() { return playerDeck; }
Deck& PlayState::getAIDeck() { return aiDeck; }
Hand& PlayState::getPHand() { return playerHand; }
Hand& PlayState::getAIHand() { return aiHand; }
Table& PlayState::getPile() { return pile; }
Turn& PlayState::getTurn() { return turn; }
GameOver& PlayState::getGO() { return gameOver; }
Player& PlayState::getPlayer() { return player; }
AI& PlayState::getAI() { return ai; }
int& PlayState::getScore() { return score; }
Bonuses& PlayState::getBonuses() { return bonuses; }
Variables& PlayState::getVars() { return variables; }

void PlayState::pDraw()
{
	if (!(playerDeck.getSize() < 1))
	{
		playerHand.addCard(playerDeck.draw());
		variables.draws++;
		bonuses.noDraw = false;
	}
	else
	{
		gameOver = NOPLAYERDECK;
	}
}