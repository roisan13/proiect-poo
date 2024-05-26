//
// Created by Radu on 5/26/2024.
//

#include "Minion.h"

#ifndef OOP_MINIONHEAL_H
#define OOP_MINIONHEAL_H

#include "Exceptions.h"

class MinionHeal : public Minion {
private:
    int healOnDeath;
public:
    MinionHeal(int hp, sf::Font &font, const std::string &textureString, sf::Vector2f size,
               const std::string &attackerTxtrString, int attackDamage_, int healOnDeath_);

    Minion *clone() const override;

    void onDeathSpell(std::vector<Minion *> &allyUnits, std::vector<Minion *> &enemyUnits) override;
};


#endif //OOP_MINIONHEAL_H
