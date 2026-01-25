#pragma once

enum GameState
{
    MENU,
    PLAY,
    SHOP
};

class StateManager
{
private:
    GameState curState;
    bool paused;
public:
    GameState getState();
    void setState(GameState newState);
    bool isPaused();
};