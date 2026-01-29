#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Card.hpp"
#include "Button.hpp"

extern unsigned int windowWidth;
extern unsigned int windowHeight;

// The possible states of a card. A card can be all states at a time.
struct CardState
{
    bool played = false;
    bool disabled = false;
    bool flipped = false;
    bool selectable = true; bool selected = false;
    bool hovered = false;
};

// MiddleCard. It sits in between the Logic Card from Card.cpp and the Graphical Card, the one inaccessible by the program.
// Its sole purpose is to connect the two.
struct MiddleCard
{
    std::shared_ptr<Card> logicCard;
    sf::RectangleShape sprite; // Temporary
    CardState state;

    MiddleCard(std::shared_ptr<Card> c, sf::RectangleShape s, CardState st) : logicCard(c), sprite(s), state(st) {};
};

class GFX
{
private:

public:
    static MiddleCard layoutCard(std::shared_ptr<Card> card, sf::Vector2f position, CardState state);
    static void drawCard(MiddleCard middleCard, sf::RenderWindow& window);
    static std::vector<float> calculateHandPos(std::vector<std::shared_ptr<Card>> hand);
};