#pragma once
#include "Trinkets.hpp"
#include "Consumables.hpp"
#include <vector>

class Player
{
private:
    std::vector<Trinkets> trinketInventory;
    std::vector<Consumables> consumableInventory;
public:
    std::vector<Trinkets> getTrinkets();
    std::vector<Consumables> getConsumables();
    std::vector<Trinkets> addTrinket();
    std::vector<Consumables> addConsumable();
};