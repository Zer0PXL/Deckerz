#include "Button.hpp"
#include <string>
using namespace std;

Button::Button(string name, sf::Texture& texture, GameState state, bool hovered, bool pressed, bool clicked) : name(name), sprite(texture), hovered(hovered), pressed(pressed), clicked(clicked) {}

sf::Sprite& Button::getSprite()
{
    return sprite;
}

string Button::getName()
{
    return name;
}