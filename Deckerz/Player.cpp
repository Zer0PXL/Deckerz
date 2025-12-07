#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <memory>
#include "Player.hpp"
#include "Card.hpp"
#include "Hand.hpp"
#include "Deck.hpp"
#include "Table.hpp"
#include "Round.hpp"
#include "Debug.hpp"
#include "AI.hpp"
#include "Consumable.hpp"
using namespace std;

enum Choice
{
	PLAY,
	PLAYMULTI,
	DRAW,
	INVALID,
	BYPASS
};

void Player::playTurn(GameState& gs)
{
	// THIS WHOLE BLOCK IS CLI!!!

/*    // Player inputs
	Choice choice = INVALID;
	std::vector<std::shared_ptr<Card>> multiPlay;
	std::string stringInput = "";
	int intInput = 0;
	bool playing = true;
    
    playing = true;

			while (playing)
			{
				std::cout << "What would you like to do? play or draw: ";

				std::cin >> stringInput;

				if (stringInput == "debug") 
				{
					Debug::toggleDebugMode();
					choice = INVALID;
				}
				if (stringInput == "cheats") 
				{
					Debug::toggleCheats();
					choice = INVALID;
				}
				if (debugMode && stringInput == "difficulty=noai") 
				{
					gs.ai.changeDifficulty(NOAI);
					choice = INVALID;
				}
				if (debugMode && stringInput == "difficulty=dumb") 
				{
					gs.ai.changeDifficulty(DUMB);
					choice = INVALID;
				}
				if (debugMode && stringInput == "difficulty=smart") 
				{
					gs.ai.changeDifficulty(SMART);
					choice = INVALID;
				}
				if (debugMode && stringInput == "difficulty=cheater") 
				{
					gs.ai.changeDifficulty(CHEATER);
					choice = INVALID;
				}
				if (debugMode && stringInput == "logturn") 
				{
					Debug::logTurn(gs);
					choice = INVALID;
				}
				if (debugMode && stringInput == "iwinbtw")
				{
					gs.gameOver = PLAYERWIN;
					choice = BYPASS;
				}
				if (debugMode && stringInput == "useMAGIC")
				{
					std::cout << "Which one? (EXTRA, GLUETUBE, LOVE, HATE, RICH, TREE, MORE, LESS, SWORD, SPEAR, SHIELD, PEEKABOO, BLANK, LOSTCRAYON, RIP, WILDACE, ADOLLAH, COINFLIP, SMOKEBOMB) ";

					std::cin >> stringInput;

					if (stringInput == "EXTRA")
					{
						Consumable::useMAGIC(EXTRA, gs);
						choice = INVALID;
					}

					else if (stringInput == "GLUETUBE")
					{
						Consumable::useMAGIC(GLUETUBE, gs);
						choice = INVALID;
					}

					else if (stringInput == "LOVE") 
					{
						Consumable::useMAGIC(LOVE, gs);
						choice = INVALID;
					}

					else if (stringInput == "HATE")
					{
						Consumable::useMAGIC(HATE, gs);
						choice = INVALID;
					}

					else if (stringInput == "RICH") 
					{
						Consumable::useMAGIC(RICH, gs);
						choice = INVALID;
					}

					else if (stringInput == "TREE") 
					{
						Consumable::useMAGIC(TREE, gs);
						choice = INVALID;
					}

					else if (stringInput == "MORE") 
					{
						Consumable::useMAGIC(MORE, gs);
						choice = INVALID;
					}

					else if (stringInput == "LESS") 
					{
						Consumable::useMAGIC(LESS, gs);
						choice = INVALID;
					}

					else if (stringInput == "SWORD") 
					{
						Consumable::useMAGIC(SWORD, gs);
						choice = INVALID;
					}

					else if (stringInput == "SPEAR") 
					{
						Consumable::useMAGIC(SPEAR, gs);
						choice = INVALID;
					}

					else if (stringInput == "SHIELD") 
					{
						Consumable::useMAGIC(SHIELD, gs);
						choice = INVALID;
					}

					else if (stringInput == "PEEKABOO") 
					{
						Consumable::useMAGIC(PEEKABOO, gs);
						choice = INVALID;
					}

					else if (stringInput == "BLANK") 
					{
						Consumable::useMAGIC(BLANK, gs);
						choice = INVALID;
					}

					else if (stringInput == "LOSTCRAYON") 
					{
						Consumable::useMAGIC(LOSTCRAYON, gs);
						choice = INVALID;
					}
					
					else if (stringInput == "RIP") 
					{
						Consumable::useMAGIC(RIP, gs);
						if (gs.playerHand.getSize() == 0)
						{
							choice = BYPASS;
						}
						else choice = INVALID;
					}

					else if (stringInput == "WILDACE") 
					{
						Consumable::useMAGIC(WILDACE, gs);
						choice = INVALID;
					}

					else if (stringInput == "ADOLLAH") 
					{
						Consumable::useMAGIC(ADOLLAH, gs);
						choice = INVALID;
					}

					else if (stringInput == "COINFLIP") 
					{
						Consumable::useMAGIC(COINFLIP, gs);
						choice = INVALID;
					}

					else if (stringInput == "SMOKEBOMB") 
					{
						Consumable::useMAGIC(SMOKEBOMB, gs);
						choice = INVALID;
					}

					else
					{
						std::cout << "Not a MAGIC card!";
						choice = INVALID;
					}
				}

				if (stringInput == "play") choice = PLAYMULTI;
				else if (stringInput == "draw") choice = DRAW;

				switch (choice)
				{

				case PLAYMULTI:
					std::cout << "Play what? Give IDs, then type -1: ";

					do
					{
						std::cin >> intInput;
						for (int i = 0; i < gs.playerHand.getSize(); i++)
						{
							if (gs.playerHand.getHand()[i]->getID() == intInput)
							{
								gs.playerHand.getHand()[i]->actAbility(gs);
								gs.playerHand.getHand()[i]->actEnhancement(gs);
								multiPlay.push_back(gs.playerHand.getHand()[i]);

								break;
							}
						}
					} while (intInput != -1);

					if (!multiPlay.empty())
					{
						gs.playerHand.playCards(multiPlay, gs);
						playing = false;
					}

					if (playing) std::cout << "Couldn't play those cards!\n";

					break;
				case DRAW:
					if (!(gs.playerDeck.getSize() < 1))
					{
						gs.playerHand.addCard(gs.playerDeck.draw());
						gs.variables.draws++;
						gs.bonuses.noDraw = false;
					}
					else
					{
						gs.gameOver = NOPLAYERDECK;
					}
					playing = false;
					break;
				case BYPASS:
					playing = false;
					break;
				}
			}*/
}