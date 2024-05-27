//
// Created by Radu on 5/27/2024.
//

#ifndef OOP_MINIONDMGHEAL_H
#define OOP_MINIONDMGHEAL_H


#include "Minion.h"

class MinionDmgHeal : public Minion {
private:
    int damageOnDeath, healOnDeath;
public:
    MinionDmgHeal(int hp, sf::Font &font, const std::string &textureString, sf::Vector2f size,
                  const std::string &attackerTxtrString, int attackDamage_, int damageOnDeath_, int healOnDeath_);

    Minion *clone() const override;

    void onDeathSpell(std::vector<Minion *> &allyUnits, std::vector<Minion *> &enemyUnits) override;
};


#endif //OOP_MINIONDMGHEAL_H
