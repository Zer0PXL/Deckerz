#pragma once

enum class GameState
{
    Menu,
    Play,
    Shop
};

class StateManager
{
private:
    GameState curState;
    bool paused = false;
public:
    GameState getState();
    void setState(GameState newState);
    bool isPaused();
};