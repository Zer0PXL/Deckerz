#pragma once
#include "StateManager.hpp"
#include "Deck.hpp"
#include "Hand.hpp"
#include "Table.hpp"
#include "AI.hpp"
#include "Inventory.hpp"
#include <unordered_map>
#include "GFX.hpp"
#include "UI.hpp"
#include <memory>

enum class Turn { Player, AI };

enum class GameOver { NotOver, PlayerWin, AIWin, NoPlayerDeck, NoAIDeck };

struct Variables { int draws = 0; int attacks = 0; int skips = 0; };

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
	Inventory inventory;
	Hand playerHand;
	Hand aiHand;
	Table pile;
	Turn turn;
	GameOver gameOver;
	AI ai;
	int score;
	Bonuses bonuses;
	Variables variables;
public:
	PlayState();
	
	void isGameOver();
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
	Inventory& getInventory();
	AI& getAI();
	int& getScore();
	Bonuses& getBonuses();
	Variables& getVars();

	void actAbility(std::shared_ptr<Card> card);
	void actEnhancement(std::shared_ptr<Card> card);

	void playerDraw();
	void playerPlay(const std::vector<std::shared_ptr<Card>> cards);

	// This function serves as a way for PlayState and UI to communicate with each other indirectly
	// It returns bools to tell you if the Cards are legal or not
	bool playMCs(std::unordered_map<int, MiddleCard> mCs);
	// This function serves as a way for PlayState and UI to communicate with each other indirectly
	// It returns bools to tell you if the Interactions are legal or not
	bool PIHandler(Interactions interacts);

	void aiPlay(const std::vector<std::shared_ptr<Card>> cards);
	void aiTurn();

	Snapshot snapshot();
};

