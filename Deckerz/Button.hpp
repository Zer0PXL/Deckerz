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

    void pushButton(); // Purely for animation
    Button(std::string name, sf::Texture& texture, GameState state, bool hovered = false, bool pressed = false, bool clicked = false) : name(name), sprite(texture), hovered(hovered), pressed(pressed), clicked(clicked) {}
public:

};