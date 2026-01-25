#pragma once

struct GameState;

enum MAGIC
{
	EXTRA, // Bonus score for playing
	GLUETUBE, // Discards random card along with the card played
	LOVE, // Turns 2 cards into Hearts
	HATE, // Turns 2 cards into Spades
	RICH, // Turns 2 cards into Diamonds
	TREE, // Turns 2 cards into Clubs
	MORE, // Increases the rank of 2 cards
	LESS, // Decreases the rank of 3 cards
	SWORD, // Turns a card into a Draw 1 card
	SPEAR, // Turns a card into a Draw 2 card
	SHIELD, // Turns a card into a Skip card
	PEEKABOO, // See the top 3 cards in your deck
	BLANK, // Use last used MAGIC card
	LOSTCRAYON, // Turn one card into another
	RIP, // Rip a card
	WILDACE, // Playable at any time to change suit
	ADOLLAH, // Gives 10 coins
	COINFLIP, // 1 in 2 chance to give 20 coins
	SMOKEBOMB, // Playable at any time to skip the AI
	INVALIDMAGIC // Just in case
};

enum ANTIMATTER
{
	INVALIDANTIMATTER
};

enum BLACKMARKET
{
	INVALIDBLACKMARKET
};

enum ConsumableType
{
	MAGICTYPE,
	ANTIMATTERTYPE,
	BLACKMARKETTYPE,
	INVALIDCONSUMABLE
};

class Consumable
{
private:
	ConsumableType type;
	MAGIC magicCard;
	ANTIMATTER antimatterCard;
	BLACKMARKET blackmarketDisk;
public:
	Consumable(ConsumableType t, MAGIC m, ANTIMATTER am);

	// Problem... So, what I'm doing right now is dumb. Who would've guessed? And I think this should work...?
	void get();

	// This is getting removed soon...
//	static void useMAGIC(MAGIC magic, PlayState& ps);
};

