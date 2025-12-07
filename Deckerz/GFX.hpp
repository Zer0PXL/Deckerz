#pragma once
#include <SFML/Graphics.hpp>
#include "Card.hpp"
#include <vector>
#include <memory>

enum cardState
{
    NORMAL,
    HOVERED,
    SELECTED,
    DISABLED
};

class GFX
{
private:

public:
    static void drawCard(std::shared_ptr<Card> card, sf::Vector2f position, cardState state, sf::RenderWindow& window);
};