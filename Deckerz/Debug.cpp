#include "Debug.hpp"
#include "Table.hpp"
#include "Hand.hpp"
#include "PlayState.hpp"
#include "AI.hpp"
#include <iostream>

Difficulty difficulty = SMART; //DUMB, SMART, CHEATER

void Debug::toggleDebugMode()
{
	if (debugMode) debugMode = false;
	else 
	{
		debugMode = true;
		Debug::log("i - Debug mode is now on.");
	}
}

void Debug::logTurn(PlayState& ps)
{
	if (ps.getTurn() == PLAYERTURN)
	{
		log("i - It's the Player's turn.");
	}
	else
	{
		log("i - It's the AI's turn");
	}
	
	std::cout << "\n";
	
	std::cout << "Pile card: "; ps.getPile().getCard()->print();

	std::cout << "\n";

	if (cheats)
	{
		std::cout << "AI hand:\n";
		for (int i = 0; i < ps.getAIHand().getHand().size(); i++)
		{
			ps.getAIHand().getHand()[i]->print();
		}

		std::cout << "\n";
	}
	else
	{
		std::cout << "AI has " << ps.getAIHand().getSize() << " cards.\n";

		std::cout << "\n";
	}

	std::cout << "Player hand:\n";
	for (int i = 0; i < ps.getPHand().getHand().size(); i++)
	{
		ps.getPHand().getHand()[i]->print();
	}

	std::cout << "\n";
}

void Debug::log(std::string text1, std::string text2, std::string text3, std::string text4, std::string text5)
{
	if (debugMode) std::cout << text1 << text2 << text3 << text4 << text5 << std::endl;
	else return;
}

void Debug::logCardVector(std::vector<Card>& cards)
{
	std::cout << "i - Cards present in vector: \n";
	
	for (int i = 0; i < cards.size(); i++) cards[i].print();
}

void Debug::toggleCheats()
{
	if (cheats) cheats = false;
	else 
	{
		cheats = true;
		std::cout << "Cheater!\n";
	}
}

std::string Debug::abilityToString(Ability a)
{
	switch (a)
	{
	case BASIC:
		return "none";
		break;
	case DRAWABILITY:
		return "draw";
		break;
	case COLOR:
		return "color";
		break;
	case SKIP:
		return "skip";
		break;
	default:
		return "invalid?????";
		break;
	}
}

std::string Debug::enhancementToString(Enhancement e)
{
	switch (e)
	{
	case EXTRAEN:
		return "extra";
		break;
	case STICKY:
		return "sticky";
		break;
	case SWORDEN:
		return "sword";
		break;
	case SPEAREN:
		return "spear";
		break;
	case SHIELDEN:
		return "shield";
		break;
	case NONE:
		return "none";
		break;
	default:
		return "invalid????????";
		break;
	}
}