//
// Created by Radu on 6/11/2024.
//

#ifndef OOP_MINION_FACTORY_H
#define OOP_MINION_FACTORY_H

#include "MinionDmg.h"
#include "MinionHeal.h"
#include "MinionDmgAll.h"
#include "MinionDmgHeal.h"
#include "SFML/Graphics.hpp"

class Minion_Factory {
private:
    static sf::Vector2f iconSize;
public:
    Minion_Factory() = default;

    static MinionDmgAll raduBuzescu(sf::Font &font) {
        return {10, font, "sprites/radu.png", iconSize, "sprites/raduAttacker.png", 2, 3};
    }

    static MinionHeal popa(sf::Font &font) {
        return {15, font, "sprites/popa.png", iconSize, "sprites/popaAttacker.png", 2, 3};
    }

    static MinionDmgHeal predaBuzescu(sf::Font &font) {
        return {11, font, "sprites/preda.png", iconSize, "sprites/predaAttacker.png", 3, 3, 3};
    }

    static MinionDmg stroeBuzescu(sf::Font &font) {
        return {8, font, "sprites/stroe.png", iconSize, "sprites/stroeAttacker.png", 2, 1};
    }
};


#endif //OOP_MINION_FACTORY_H
