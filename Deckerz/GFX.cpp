#include "GFX.hpp"
#include <iostream>
#include "Debug.hpp"
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>

sf::Font font("Resources/ARIAL.TTF");

sf::RectangleShape sprite;
sf::Text cardRank(font);
sf::Text cardSuit(font);
sf::Text debugText(font); std::string debugString;

unsigned int windowWidth = 1280;
unsigned int windowHeight = 720;

// This function places the MiddleCard, creating an object accessible by both the program and the player.
MiddleCard GFX::layoutCard(std::shared_ptr<Card> card, sf::Vector2f position, CardState state)
{
    sprite.setSize({150, 200});
    sprite.setOrigin({75, 100});
    sprite.setPosition(position);

    // replace this later with extracting the correct texture from the spritesheet
    sprite.setFillColor(sf::Color::White);

    MiddleCard mC(card->getID(), sprite, card->getRank(), card->getSuit(), state);
    return mC;
}

// Just takes the MiddleCard and draws it to the screen
void GFX::drawCard(MiddleCard mC, sf::RenderWindow& window)
{
    float OffsetY = 0;

    cardRank.setString(std::to_string(mC.rank));
    cardRank.setCharacterSize(24);
    cardRank.setFillColor(sf::Color::Black);
    cardRank.setPosition({mC.sprite.getPosition().x - 60, mC.sprite.getPosition().y - 12});

    if (mC.suit == HEARTS)
        cardSuit.setString("of Hearts");
    else if (mC.suit == SPADES)
        cardSuit.setString("of Spades");
    else if (mC.suit == DIAMONDS)
        cardSuit.setString("of Diamonds");
    else if (mC.suit == CLUBS)
        cardSuit.setString("of Clubs");
    cardSuit.setFillColor(sf::Color::Black);
    cardSuit.setCharacterSize(24);
    cardSuit.setPosition({mC.sprite.getPosition().x + 25 - 60, mC.sprite.getPosition().y - 12});

    if (debugMode)
    {
        debugString = std::to_string(mC.ucid);

        if (!mC.state.selectable) debugString += " !selectable";

        if (mC.state.disabled) debugString += " disabled";
        if (mC.state.flipped) debugString += " flipped";
        if (mC.state.selected) debugString += " selected";
        if (mC.state.hovered) debugString += " hovered";

        debugText.setFillColor(sf::Color::Red);
        debugText.setOutlineThickness(5.f);
        debugText.setOutlineColor(sf::Color::Black);
        debugText.setPosition({mC.sprite.getPosition().x - 60.f, mC.sprite.getPosition().y - 100.f});
        debugText.setString(debugString);
    }

    if (mC.state.selected) OffsetY = 35;
    else if (mC.state.hovered) OffsetY = 15;

    mC.sprite.setPosition({mC.sprite.getPosition().x, mC.sprite.getPosition().y - OffsetY});
    cardRank.setPosition({cardRank.getPosition().x, cardRank.getPosition().y - OffsetY});
    cardSuit.setPosition({cardSuit.getPosition().x, cardSuit.getPosition().y - OffsetY});
    debugText.setPosition({debugText.getPosition().x, debugText.getPosition().y});

    window.draw(mC.sprite);
    window.draw(cardRank);
    window.draw(cardSuit);
    if (debugMode) window.draw(debugText);
}

std::vector<float> GFX::calculateHandPos(std::vector<std::shared_ptr<Card>> hand)
{
    std::vector<float> pos;
    float ratio = hand.size();

    for (float i = 1; i <= ratio; i++)
    {
        pos.push_back((windowWidth - 200) * i/ratio);
    }

    return pos;
}

void Button::pushButton()
{
    // Placeholder for now, because I have no idea how to animate
}