#include "GFX.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

sf::RectangleShape sprite;
sf::Font font("Resources/ARIAL.TTF");
sf::Text cardRank(font);

void GFX::drawCard(std::shared_ptr<Card> card, sf::Vector2f position, cardState state, sf::RenderWindow& window)
{
    sprite.setSize({150, 200});
    sprite.setPosition(position);
    sprite.setOrigin({75, 100});
    // replace this later with extracting the correct sprite from the spritesheet
    sprite.setFillColor(sf::Color::White);
    window.draw(sprite);

    cardRank.setString(std::to_string(card->getRank()));
    cardRank.setCharacterSize(24);
    if (card->getSuit() == HEARTS)
        cardRank.setFillColor(sf::Color::Red);
    else if (card->getSuit() == SPADES)
        cardRank.setFillColor(sf::Color::Black);
    else if (card->getSuit() == DIAMONDS)
        cardRank.setFillColor(sf::Color::Yellow);
    else if (card->getSuit() == CLUBS)
        cardRank.setFillColor(sf::Color::Green);
    cardRank.setPosition(position);
    window.draw(cardRank);
}