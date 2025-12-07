#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "Card.hpp"
#include "Hand.hpp"
#include "Deck.hpp"
#include "Table.hpp"
#include "Round.hpp"
#include "Debug.hpp"
#include "AI.hpp"
#include "Consumable.hpp"
#include "Player.hpp"
#include <memory>
#include "GFX.hpp"
using namespace std;
using namespace sf;

#ifdef DEBUG
bool debugMode = true;
bool cheats = true;
#else
bool debugMode = false;
bool cheats = false;
#endif

enum Choice
{
	PLAY,
	PLAYMULTI,
	DRAW,
	INVALID,
	BYPASS
};

int main()
{
	std::cout << "Deckerz v0\n";

	// Graphics objects (oh boy)
	RenderWindow window(VideoMode({1280, 720}), "Deckerz");
	float x = 300.0, y = 300.0;

	// Game objects
	Player player;
	AI ai;
	Deck playerDeck = Deck(PLAYER);
	Deck aiDeck = Deck(OWNERAI);
	Hand playerHand;
	Hand aiHand;
	Table pile;
	Turn turn;
	GameOver gameOver = NOTOVER;
	int turnNr = 0;
	int score = 0;
	Bonuses bonuses;
	Variables variables;
	bool running = true;
	
	// GameState and Round creation
	GameState gs{ playerDeck, aiDeck, playerHand, aiHand, pile, turn, gameOver, ai, score, bonuses, variables };
	Round round = Round(gs);
	Round::resetBonuses(gs);

	// Start of SFML window loop
	while (window.isOpen())
	{
		while (const optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
                window.close();
		}

		/*// Are we in a round?
		if (round.isGameOver(gs) == NOTOVER)
		{	
			turnNr++;
			
			Debug::logTurn(gs);

			if (turn == PLAYERTURN)
			{
				Round::switchTurn(gs);
				player.playTurn(gs);
			}
			else
			{
				Round::switchTurn(gs);
				gs.ai.playTurn(gs);
			}

			if (gs.playerHand.getSize() >= 10)
			{
				gs.bonuses.comeback = true;
			}

		}
		// If not, guess the round is over. (this is very bad, don't do this)
		else
		{
			if (turnNr > 1) gs.bonuses.oneShotWonder = false;
			if (turnNr > 5) gs.bonuses.speedster = false;

			round.endRound(gs);

			std::cout << "\nGame Over!\n";

			switch (round.isGameOver(gs))
			{
			case NOTOVER:
							std::cout << "! - Uhh... The game wasn't supposed to end...\n";
							break;
			case PLAYERWIN:
							std::cout << "The Player wins!\n";
							break;
			case AIWIN:
							std::cout << "The AI wins!\n";
							break;
			case NOPLAYERDECK:
							std::cout << "The Player ran out of cards! AI wins!\n";
							break;
			case NOAIDECK:
							std::cout << "The AI ran out of cards! Player wins!\n";
							break;
			default:
							std::cout << "X - Garbage data in GameOver???\n";
							break;
			}

			Round::calculateBonuses(gs);

			std::cout << "Your score!" << std::endl;
			std::cout << "=============================\n| " << gs.score << "|\n=============================\n";
		}*/
	
		// GUI functions
		window.clear(Color::Black);

		for (int i = 0; i < gs.playerHand.getSize(); i++)
			GFX::drawCard(gs.playerHand.getHand()[i], {x + i * 100, y}, NORMAL, window);

		window.display();
	
	}

	return 0;
}