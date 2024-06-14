//
// Created by Radu on 6/11/2024.
//

#ifndef OOP_MINION_BUILDER_H
#define OOP_MINION_BUILDER_H

#include "MinionDmg.h"

class Minion_Builder {
private:
    MinionDmg otoman;

public:
    Minion_Builder() = default;

//    MinionDmg(int hp, sf::Font &font, const std::string &textureString, sf::Vector2f size,
//              const std::string &attackerTxtrString, int attackDamage_, int damageOnDeath_);

    Minion_Builder &health(int val);

    Minion_Builder &font(sf::Font &font);

    Minion_Builder &texture(const std::string &textureString);

    Minion_Builder &attackerTexture(const std::string &attackerTxtrString);

    Minion_Builder &size(sf::Vector2f size_);

    Minion_Builder &attackDamage(int attackDamage_);

    Minion_Builder &damageOnDeath(int damageOnDeath_);

    MinionDmg build();


};

#endif //OOP_MINION_BUILDER_H
