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
    bool disabled = false;
    bool flipped = false;
    bool selectable = true; bool selected = false;
    bool hovered = false;
};

// MiddleCard. It sits in between the LogicCard from Card.cpp and the Graphical Card, the one inaccessible by the program.
// Its sole purpose is to connect the two.
struct MiddleCard
{
    sf::RectangleShape sprite; // Temporary

    int ucid;
    int rank;
    int suit;
    CardState state;

    MiddleCard(int ucid, sf::RectangleShape s, int cR, int cS, CardState st) : ucid(ucid), sprite(s), rank(cR), suit(cS), state(st) {};
};

class GFX
{
private:

public:
    static MiddleCard layoutCard(std::shared_ptr<Card> card, sf::Vector2f position, CardState state);
    static void drawCard(MiddleCard middleCard, sf::RenderWindow& window);
    static std::vector<float> calculateHandPos(std::vector<std::shared_ptr<Card>> hand);
};