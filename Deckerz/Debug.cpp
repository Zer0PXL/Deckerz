#include "Debug.hpp"
#include "Table.hpp"
#include "Hand.hpp"
#include "PlayState.hpp"
#include "AI.hpp"
#include <iostream>

void Debug::toggleDebugMode()
{
	if (debugMode) debugMode = false;
	else 
	{
		debugMode = true;
		Debug::log("i - Debug mode is now on.");
	}
}

void Debug::log(std::string text1, std::string text2, std::string text3, std::string text4, std::string text5)
{
	if (debugMode) std::cout << text1 << text2 << text3 << text4 << text5 << std::endl;
	else return;
}

void Debug::logCardVector(std::vector<std::shared_ptr<Card>>& cards)
{
	std::cout << "i - Cards present in vector: \n";
	
	for (int i = 0; i < cards.size(); i++) cards[i]->print();
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