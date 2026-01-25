#include <random>
#include <iostream>
#include "PlayState.hpp"
#include "Hand.hpp"
#include "Chance.hpp"
#include "Debug.hpp"

PlayState::PlayState() : playerDeck(PLAYER), aiDeck(OWNERAI), gameOver(GameOver::NotOver), score(0)
{
	Debug::log("[PlayState.cpp] Starting PlayState...");

	// Shuffle decks
	playerDeck.shuffle();
	aiDeck.shuffle();

	// Each player draws 5 cards
	if (playerDeck.getSize() < 1)
	{
		gameOver = GameOver::NoPlayerDeck;
	}
	for (int i = 1; i <= 5; i++)
	{
		playerHand.addCard(playerDeck.draw());
		aiHand.addCard(aiDeck.draw());
	}

	// Flip a coin to determine first-goer
	if (Chance::chance(1, 2) == 1) turn = Turn::Player;
	else turn = Turn::AI;

	// Draw a card to the pile
	Debug::log("[PlayState.cpp] Drawing a card from the loser's deck...");
	if (turn == Turn::Player) pile.addCard(aiDeck.draw());
	else pile.addCard(playerDeck.draw());
}

void PlayState::isGameOver()
{	
	if (gameOver == GameOver::NotOver)
	{
		if (playerHand.getHand().size() == 0)
		{
			gameOver = GameOver::PlayerWin;
		}
		else if (aiHand.getHand().size() == 0)
		{
			gameOver = GameOver::AIWin;
		}
		else
		{
			gameOver = GameOver::NotOver;
		}
	}
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
	if (turn == Turn::Player) turn = Turn::AI;
	else turn = Turn::Player;
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

	if (gameOver == GameOver::PlayerWin || gameOver == GameOver::NoAIDeck)
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
Inventory& PlayState::getInventory() { return inventory; }
AI& PlayState::getAI() { return ai; }
int& PlayState::getScore() { return score; }
Bonuses& PlayState::getBonuses() { return bonuses; }
Variables& PlayState::getVars() { return variables; }

void PlayState::actAbility(std::shared_ptr<Card> card)
{
	Hand* targetHand = &aiHand;
	Deck* targetDeck = &aiDeck;
	
	if (card->getOwner() == OWNERAI)
	{
		targetHand = &playerHand;
		targetDeck = &playerDeck;
	}

	switch (card->getAbility())
	{
	case DRAWABILITY:
		Debug::log("[Card.cpp] DRAWABILITY");
		if (card->getRank() == 2 || card->getEnhancement() == SPEAREN)
		{
			for (int i = 1; i <= 2; i++)
			{
				if (targetDeck->getSize() > 0)
				{
					targetHand->addCard(targetDeck->draw());
					if (card->getOwner() == PLAYER) variables.attacks++;
				}
				else
				{
					if (card->getOwner() == OWNERAI)
					{
						gameOver = GameOver::NoPlayerDeck;
					}
					else gameOver = GameOver::NoAIDeck;
				}
			}
		}
		else if (card->getRank() == 3)
		{
			for (int i = 1; i <= 3; i++)
			{
				if (targetDeck->getSize() > 0)
				{
					 targetHand->addCard(targetDeck->draw());
					 if (card->getOwner() == PLAYER) variables.attacks++;
				}
				else
				{
					if (card->getOwner() == OWNERAI)
					{
						gameOver = GameOver::NoPlayerDeck;
					}
					else gameOver = GameOver::NoAIDeck;
				}
			}
		}
		else if (card->getRank() == -1)
		{
			for (int i = 1; i <= 5; i++)
			{
				if (targetDeck->getSize() > 0)
				{
					targetHand->addCard(targetDeck->draw());
					if (card->getOwner() == PLAYER) variables.attacks++;
				}
				else
				{
					if (card->getOwner() == OWNERAI)
					{
						gameOver = GameOver::NoPlayerDeck;
					}
					else gameOver = GameOver::NoAIDeck;
				}
			}
		}
		else if (card->getEnhancement() == SWORDEN)
		{
			if (targetDeck->getSize() > 0)
			{
				targetHand->addCard(targetDeck->draw());
				if (card->getOwner() == PLAYER) variables.attacks++;
			}
			else
			{
				if (card->getOwner() == OWNERAI)
				{
					gameOver = GameOver::NoPlayerDeck;
				}
				else gameOver = GameOver::NoAIDeck;
			}
		}
		else
		{
			std::cout << "X - Invalid card for DRAWABILITY (how!?!)\n";
		}

		if (card->getOwner() == PLAYER) 
		{
			Debug::log("i - The Player should be next, since they played a draw card.");
			turn = Turn::Player;
		}
		else turn = Turn::AI;
		break;
	case COLOR:
		Debug::log("[Card.cpp] COLOR");
		if (card->getOwner() == PLAYER)
		{
			// Will replace this with a fun GUI thing
			/*std::string stringInput;
			Suit suitToChangeTo = HEARTS;
			std::cout << "What suit do you want? (hearts, spades, diamonds, clubs)";
			//std::cin >> stringInput;

			if (stringInput == "hearts") suitToChangeTo = HEARTS;
			else if (stringInput == "spades") suitToChangeTo = SPADES;
			else if (stringInput == "diamonds") suitToChangeTo = DIAMONDS;
			else if (stringInput == "clubs") suitToChangeTo = CLUBS;
			else std::cout << "That's not a suit!";

			ps.getPile().addCard(std::make_shared<Card>(1, suitToChangeTo, 0, NOOWNER, BASIC, NONE));*/
		}
		else
		{
			if (ai.getDifficulty() == Difficulty::Dumb)
			{
				int randomChance = Chance::chance(0, 3);
				Suit randomSuit;
				switch (randomChance)
				{
				case 0:
					randomSuit = HEARTS;
					break;
				case 1:
					randomSuit = SPADES;
					break;
				case 2:
					randomSuit = DIAMONDS;
					break;
				case 3:
					randomSuit = CLUBS;
					break;
				default:
					randomSuit = HEARTS;
					std::cout << "[PlayState.cpp] X - Chance returned invalid interger!\n";
					break;
				}
				pile.addCard(std::make_shared<Card>(1, randomSuit, 0, NOOWNER, BASIC, NONE));
			}
			else if (ai.getDifficulty() == Difficulty::Smart)
			{
				Suit suitToChangeTo;
				switch (ai.determineBestSuit())
				{
				case HEARTS:
					suitToChangeTo = HEARTS;
					break;
				case SPADES:
					suitToChangeTo = SPADES;
					break;
				case DIAMONDS:
					suitToChangeTo = DIAMONDS;
					break;
				case CLUBS:
					suitToChangeTo = CLUBS;
					break;
				default:
					suitToChangeTo = HEARTS;
					std::cout << "X - Invalid best suit!\n";
					break;
				}
				pile.addCard(std::make_shared<Card>(1, suitToChangeTo, 0, NOOWNER, BASIC, NONE));
			}
		}
		break;
	case SKIP:
		Debug::log("[Card.cpp] SKIP");
		if (card->getOwner() == PLAYER)
		{
			turn = Turn::Player;
		}
		else if (card->getOwner() == OWNERAI) turn = Turn::AI;
		else std::cout << "[PlayState.cpp] X - uh... SKIP ability called by invalid card with no owner?\n";
		break;
	default:
		Debug::log("[PlayState.cpp] BASIC or other ability card. Skipping...");
		return;
		break;
	}
}

void PlayState::playerDraw()
{
	if (!(playerDeck.getSize() < 1))
	{
		playerHand.addCard(playerDeck.draw());
		variables.draws++;
		bonuses.noDraw = false;
	}
	else
	{
		gameOver = GameOver::NoPlayerDeck;
	}
}

void PlayState::playerPlay(const std::vector<std::shared_ptr<Card>> cards)
{
	std::vector<std::shared_ptr<Card>> toPlay;
	std::vector<int> toBeDeleted;

	for (int i = 0; i < playerHand.getHand().size(); i++)
	{
		for (int j = 0; j < cards.size(); j++)
		{
			if (cards[j]->getID() == playerHand.getHand()[i]->getID())
			{
				toPlay.push_back(playerHand.getHand()[i]);
				toBeDeleted.push_back(i);

				break;
			}
		}
	}

	if (toPlay.size() < 1)
	{
		Debug::log("[PlayState.cpp] ! - No cards for playCards (how?)");

		toPlay = { std::make_shared<Card>(0, HEARTS, -1, NOOWNER, BASIC, NONE) };
	}

	int rankCheck = toPlay[0]->getRank();
	for (int i = toPlay.size()-1; i >= 0; i--)
	{
		if (toPlay[i]->getRank() != rankCheck)
		{
			toPlay.erase(toPlay.begin() + i);
			toBeDeleted.erase(toBeDeleted.begin() + i);
		}
	}

	std::shared_ptr<Card> currentTop = pile.getCard();

	for (int i = 0; i < toPlay.size(); i++)
	{
		Debug::log("[PlayState.cpp] Checking if the card is playable...");
		if (Card::isPlayable(toPlay[i], currentTop))
		{
			if (!(toPlay[i]->getAbility() == COLOR))
			{
				pile.addCard(toPlay[i]);
			}
			if (toPlay[i]->getAbility() == COLOR && !(pile.getCard()->getOwner() == NOOWNER))
			{
				pile.addCard(toPlay[i]);
			}
			std::cout << "Played: "; toPlay[i]->print(); std::cout << "\n";
			currentTop = pile.getCard();
		}
		else
		{
			std::cout << "Not playable!\n";
			if (turn == Turn::AI) turn = Turn::Player;
		}
	}

	for (int i = toPlay.size() - 1; i >= 0; i--)
	{
		playerHand.removeCard(toPlay[i]);
	}
}

void PlayState::aiPlay(const std::vector<std::shared_ptr<Card>> cards)
{
	std::vector<std::shared_ptr<Card>> toPlay;
	std::vector<int> toBeDeleted;

	for (int i = 0; i < aiHand.getHand().size(); i++)
	{
		for (int j = 0; j < cards.size(); j++)
		{
			if (cards[j]->getID() == aiHand.getHand()[i]->getID())
			{
				toPlay.push_back(aiHand.getHand()[i]);
				toBeDeleted.push_back(i);

				break;
			}
		}
	}

	if (toPlay.size() < 1)
	{
		Debug::log("[PlayState.cpp] ! - No cards for playCards (how?)");

		toPlay = { std::make_shared<Card>(0, HEARTS, -1, NOOWNER, BASIC, NONE) };
	}

	int rankCheck = toPlay[0]->getRank();
	for (int i = toPlay.size()-1; i >= 0; i--)
	{
		if (toPlay[i]->getRank() != rankCheck)
		{
			toPlay.erase(toPlay.begin() + i);
			toBeDeleted.erase(toBeDeleted.begin() + i);
		}
	}

	std::shared_ptr<Card> currentTop = pile.getCard();

	for (int i = 0; i < toPlay.size(); i++)
	{
		Debug::log("[PlayState.cpp] Checking if the card is playable...");
		if (Card::isPlayable(toPlay[i], currentTop))
		{
			if (!(toPlay[i]->getAbility() == COLOR))
			{
				pile.addCard(toPlay[i]);
			}
			if (toPlay[i]->getAbility() == COLOR && !(pile.getCard()->getOwner() == NOOWNER))
			{
				pile.addCard(toPlay[i]);
			}
			std::cout << "Played: "; toPlay[i]->print(); std::cout << "\n";
			currentTop = pile.getCard();
		}
		else
		{
			Debug::log("[PlayState.cpp] X - AI tried to play an impossible card?!");
			return;
		}
	}

	for (int i = toPlay.size() - 1; i >= 0; i--)
	{
		aiHand.removeCard(toPlay[i]);
	}
}

void PlayState::aiTurn()
{
	std::cout << "============================\n" << "The AI is thinking...\n" << "============================\n";
	if (turn != Turn::AI) std::cout << "[AI.cpp] X - It's not the AI's turn, but somehow, it's playing???\n";
	
	bonuses.oneManShow = false;
	bonuses.oneShotWonder = false;
	
	std::cout << "============================\n" << "The AI is thinking...\n" << "============================\n";

	if (ai.isSmoked())
	{
		std::cout << "*cough cough*\n";
		ai.smokeBomb();
		turn = Turn::Player;
		std::cout << "============================\n" << "AI's turn is over\n" << "============================\n";
		return;
	}

	// Purely for debug purposes
	// Just plays the first legal card(s), if it can't play anything, just draw.
	if (ai.getDifficulty() == Difficulty::NoAI)
	{
		std::cout << "Nevermind! It's off!\n";
	}
	// Easy mode.
	else if (ai.getDifficulty() == Difficulty::Dumb)
	{
		const std::vector<std::shared_ptr<Card>>& hand = aiHand.getHand();
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

		std::shared_ptr<Card> temporaryCard = std::make_shared<Card>(0, HEARTS, 0, NOOWNER, BASIC, NONE);
		std::vector<std::shared_ptr<Card>> temporaryCards;

		if (playable.size() < 1)
		{
			// Check for deck
			if (aiDeck.getSize() == 0)
			{
				gameOver = GameOver::NoAIDeck;
			}
			else
			{
				aiHand.addCard(aiDeck.draw());
				turn = Turn::Player;
			}
		}
		else
		{
			temporaryCard = playable[0];
			aiPlay(playable);
			actAbility(temporaryCard);
		}
	}
	else if (ai.getDifficulty() == Difficulty::Smart)
	{
		// Priority queue-based gameplay.
		// Gathers the legal cards into multiple vectors and plays what's best.
		// Queue would look something like this:
		// I. Suit of most cards
		//		1. Skip cards (4s)
		//		2. Basic cards with no ability
		//		3. Draw cards (2s, 3s, Jokers)
		//		4. Color changers (Aces)
		// II. Second-best suit
		//		Same order...
		// So on until we run out of cards, then we just draw.
		// But, then, also bypassers:
		//		1. If Player has Macao (a single card) always play a Draw card.
		//		2. If Player has Macao but you don't have Draw cards, always change the color.

		ai.getHearts().clear();
		ai.getSpades().clear();
		ai.getDiamonds().clear();
		ai.getClubs().clear();
		ai.getBest().clear();

		std::vector<std::shared_ptr<Card>> jokerCards;
		std::vector<std::shared_ptr<Card>> skipCards;
		std::vector<std::shared_ptr<Card>> basicCards;
		std::vector<std::shared_ptr<Card>> drawCards;
		std::vector<std::shared_ptr<Card>> colorCards;

		// Split cards per color and if they're Jokers
		for (int i = 0; i < aiHand.getSize(); i++)
		{
			Debug::log("[AI.cpp] Checking for playable cards...");
			if (Card::isPlayable(aiHand.getHand()[i], pile.getCard()))
			{
				switch (aiHand.getHand()[i]->getSuit())
				{
				case HEARTS:
					ai.getHearts().push_back(aiHand.getHand()[i]);
					break;
				case SPADES:
					ai.getSpades().push_back(aiHand.getHand()[i]);
					break;
				case DIAMONDS:
					ai.getDiamonds().push_back(aiHand.getHand()[i]);
					break;
				case CLUBS:
					ai.getClubs().push_back(aiHand.getHand()[i]);
					break;
				default:
					jokerCards.push_back(aiHand.getHand()[i]);
					break;
				}
			}
		}

		// Determine the bestSuit (the color with the most cards)
		switch (ai.determineBestSuit())
		{
		case HEARTS:
			ai.setBest(ai.getHearts());
			break;
		case SPADES:
			ai.setBest(ai.getSpades());
			break;
		case DIAMONDS:
			ai.setBest(ai.getDiamonds());
			break;
		case CLUBS:
			ai.setBest(ai.getClubs());
			break;
		// These are here because VSC doesn't have a ignore warning option...
		case BLACKJOKER:
			break;
		case REDJOKER:
			break;
		}

		// Don't forget the Jokers!
		for (int i = 0; i < jokerCards.size(); i++)
		{
			drawCards.push_back(jokerCards[i]);
		}

		// Split the cards of the biggest color based on ability
		for (int i = 0; i < ai.getBest().size(); i++)
		{
			switch (ai.getBest()[i]->getAbility())
			{
			case SKIP:
				skipCards.push_back(ai.getBest()[i]);
				break;
			case DRAWABILITY:
				drawCards.push_back(ai.getBest()[i]);
				break;
			case COLOR:
				colorCards.push_back(ai.getBest()[i]);
				break;
			default:
				basicCards.push_back(ai.getBest()[i]);
				break;
			}
		}

		// ======== BYPASSERS ========
		// If the Player has Macao, AI should attempt to mess up the Player's lead.
		if (playerHand.getSize() < 2 && !drawCards.empty()) 
		{
			actAbility(drawCards[0]);
			aiPlay(drawCards);
		}
		else if (playerHand.getSize() < 2 && !colorCards.empty()) 
		{
			actAbility(colorCards[0]);
			aiPlay(colorCards);
		}
		// ===========================
		// Play based on the priority queue
		else if (!skipCards.empty()) 
		{
			actAbility(skipCards[0]);
			aiPlay(skipCards);
		}
		else if (!basicCards.empty()) 
		{
			aiPlay(basicCards);
		}
		else if (!drawCards.empty()) 
		{
			actAbility(drawCards[0]);
			aiPlay(drawCards);
		}
		else if (!colorCards.empty()) 
		{
			actAbility(colorCards[0]);
			aiPlay(colorCards);
		}
		else 
		{
			std::cout << "The AI draws a card...\n";
			if (!(aiDeck.getSize() < 1))
			{
				aiHand.addCard(aiDeck.draw());
			}
			else
			{
				gameOver = GameOver::NoAIDeck;
			}
		}

		jokerCards.clear();
		skipCards.clear();
		basicCards.clear();
		drawCards.clear();
		colorCards.clear();
	}
	else if (ai.getDifficulty() == Difficulty::Unfair)
	{
		gameOver = GameOver::AIWin;
	}

	std::cout << "============================\n" << "AI's turn is over\n" << "============================\n";
}