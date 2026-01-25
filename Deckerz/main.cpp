#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "Card.hpp"
#include "Hand.hpp"
#include "Deck.hpp"
#include "Table.hpp"
#include "PlayState.hpp"
#include "Debug.hpp"
#include "AI.hpp"
#include "Consumable.hpp"
#include "Inventory.hpp"
#include <memory>
#include "GFX.hpp"
#include "Button.hpp"
using namespace std;
using namespace sf;

#ifdef DEBUG
bool debugMode = true;
bool cheats = true;
#else
bool debugMode = false;
bool cheats = false;
#endif

/*enum Choice
{
	PLAY,
	PLAYMULTI,
	DRAW,
	INVALID,
	BYPASS
};*/

constexpr auto PLAYBTN = "play";
constexpr auto DRAWBTN = "draw";

int main()
{
	std::cout << "Deckerz GUI v0\n";

	// Graphics objects (oh boy)
	RenderWindow window(VideoMode({windowWidth, windowHeight}), "Deckerz GUI alpha 0");

	sf::Texture bgTexture("Resources/bg.png");
	sf::Sprite bpsprite(bgTexture);

	Texture playBtnTexture("Resources/play.png");

	sf::Vector2f pilePos = {windowWidth/2.f, windowHeight/2.f};
	sf::Vector2f mousePos;

	// MiddleCards
	std::unordered_map<int, MiddleCard> middleCards; // Uses UCID as a key
	vector<MiddleCard> selectedCards;
	CardState state;
	CardState pileState; pileState.selectable = false;

	// Buttons
	vector<Button> buttons;

	// PlayState
	PlayState ps;
	ps.resetBonuses();

	// Start of SFML window loop
	while (window.isOpen())
	{
		// Other SFML stuff
		mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

		// SFML events
		while (const optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
                window.close();
			
			if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::D)
					ps.playerDraw();
			}

			if (const auto* mbPressed = event->getIf<sf::Event::MouseButtonPressed>())
			{
				if (mbPressed->button == sf::Mouse::Button::Left)
				{
					for (auto& [ucid, middle] : middleCards) 
					{
						if (middle.sprite.getGlobalBounds().contains(mousePos) && !middle.state.selected && middle.state.selectable)
							middle.state.selected = true;
						else if (middle.sprite.getGlobalBounds().contains(mousePos))
							middle.state.selected = false;
					}
				}
			}
		}
	
		// Drawing functions
		window.clear();
		window.draw(bpsprite);

		// Laying out the player's hand and adding each card to the visualData map
		for (int i = 0; i < ps.getPHand().getHand().size(); i++)
		{
			auto emplacedSuccesfully = middleCards.try_emplace(ps.getPHand().getHand()[i]->getID(), GFX::layoutCard(ps.getPHand().getHand()[i], {GFX::calculateHandPos(ps.getPHand().getHand())[i], 600.f}, state));
			auto existingState = emplacedSuccesfully.first->second.state;
			if (!emplacedSuccesfully.second)
				middleCards.insert_or_assign(ps.getPHand().getHand()[i]->getID(), GFX::layoutCard(ps.getPHand().getHand()[i], {GFX::calculateHandPos(ps.getPHand().getHand())[i], 600.f}, existingState));
		}

		// Laying out the pile card and adding it to the visualData map
		middleCards.insert_or_assign(ps.getPile().getCard()->getID(), GFX::layoutCard(ps.getPile().getCard(), pilePos, pileState));

		// Collision detection
		for (auto& [ucid, middle] : middleCards) 
		{
			if (middle.sprite.getGlobalBounds().contains(mousePos)) middle.state.hovered = true;
			else middle.state.hovered = false;
		}

		// Iterate over every middleCard and draw it
		for (auto& [ucid, mC] : middleCards)
		{
			GFX::drawCard(mC, window);
		}

		for (auto& button : buttons)
		{
			
		}

		window.display();

	}

	return 0;
}