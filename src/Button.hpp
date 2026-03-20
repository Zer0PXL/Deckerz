#include <string>
#include <SFML/Graphics.hpp>
#include "StateManager.hpp"
#pragma once

class Button
{
private:
    std::string name;
    sf::Sprite sprite;

    bool hovered;
    bool pressed;
    bool clicked;
public:
    sf::Sprite& getSprite();
    std::string getName();

    Button(std::string name, sf::Texture& texture, GameState state, bool hovered = false, bool pressed = false, bool clicked = false);
    void pushButton(); // Purely for animation
};