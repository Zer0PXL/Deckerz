#include "StateManager.hpp"

GameState StateManager::getState() { return curState; }

void StateManager::setState(GameState newState)
{
    curState = newState;
}

bool StateManager::isPaused() { return paused; }