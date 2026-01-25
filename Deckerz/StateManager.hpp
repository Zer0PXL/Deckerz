#pragma once

enum State
{
    MENU,
    PLAY,
    SHOP
};

class StateManager
{
private:
    State curState;
    bool paused;
public:
    State getState();
    void setState(State newState);
    bool isPaused();
};