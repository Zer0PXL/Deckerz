#pragma once
#include "StateManager.hpp"
#include "Deck.hpp"
#include "Hand.hpp"
#include "Table.hpp"
#include "AI.hpp"
#include "Player.hpp"
#include <memory>

enum Turn
{
	PLAYERTURN,
	AITURN
};

enum GameOver
{
	NOTOVER,
	PLAYERWIN,
	AIWIN,
	NOPLAYERDECK,
	NOAIDECK
};

struct Variables
{
	int draws = 0;
	int attacks = 0;
	int skips = 0;
};

struct Bonuses
{
	bool speedster = true;
	bool jokester = false;
	bool royalty = false;
	bool noDraw = true;
	bool comeback = false;
	bool oneManShow = true;
	bool oneShotWonder = true;
};

class PlayState
{
private:
	Deck playerDeck;
	Deck aiDeck;
	Hand playerHand;
	Hand aiHand;
	Table pile;
	Turn turn;
	GameOver gameOver;
	Player player;
	AI ai;
	int score;
	Bonuses bonuses;
	Variables variables;
public:
	PlayState();
	
	GameOver isGameOver();
	void endRound();
	void switchTurn();
	void calculateBonuses();
	void resetBonuses();

	Deck& getPDeck();
	Deck& getAIDeck();
	Hand& getPHand();
	Hand& getAIHand();
	Table& getPile();
	Turn& getTurn();
	GameOver& getGO();
	Player& getPlayer();
	AI& getAI();
	int& getScore();
	Bonuses& getBonuses();
	Variables& getVars();

	void pDraw();
};

