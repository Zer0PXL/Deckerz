#pragma once
#include "GFX.hpp"
#include <SFML/Graphics.hpp>

// PlayerInteraction
enum class PI
{
    None,
    Play,
    Draw
};

// Dumb name, but it's the logic that goes to PlayState
struct Interactions
{
    PI playerInteraction = PI::None;
    std::unordered_map<int, MiddleCard> playedCards;
};

// A photo of the screen
// (not literally)
struct Snapshot
{
    std::vector<std::shared_ptr<Card>> playerHand;
    std::shared_ptr<Card> pileCard;
};

class UI
{
private:
    // Interactions
    sf::Vector2f mousePos;
    Interactions interacts;

    // MiddleCards
	std::unordered_map<int, MiddleCard> middleCards; // Uses UCID as a key
	std::unordered_map<int, MiddleCard> selectedCards; // Uses UCID as a key

    // Buttons
	std::vector<Button> buttons;
public:
    void setMouse(sf::Vector2f mPos);
    void resetInteracts();
    Interactions getInteracts();

    Interactions inputHandler(sf::RenderWindow& window, std::optional<sf::Event> event);
    void layoutHandler(sf::RenderWindow& window, Snapshot snapshot);
    void collisionHandler();
    void drawHandler(sf::RenderWindow& window);
};