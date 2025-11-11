#pragma once
#include "Trinket.hpp"
#include "Consumable.hpp"
#include <vector>

class Player
{
private:
    std::vector<Trinket> trinketInventory;
    std::vector<Consumable> consumableInventory;
public:
    std::vector<Trinket> getTrinkets()const ;
    std::vector<Consumable> getConsumables() const;
    void addTrinket(std::vector<Trinket>);
    void addConsumable(std::vector<Consumable>);
};