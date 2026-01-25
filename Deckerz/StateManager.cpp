#include "StateManager.hpp"

State StateManager::getState() { return curState; }

void StateManager::setState(State newState)
{
    curState = newState;
}

bool StateManager::isPaused() { return paused; }