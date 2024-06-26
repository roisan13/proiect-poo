//
// Created by Radu on 5/14/2024.
//

#ifndef OOP_MINIONDMG_H
#define OOP_MINIONDMG_H

#include "Minion.h"

class MinionDmg : public Minion {
private:
    int damageOnDeath;

    friend class Minion_Builder;
public:
    MinionDmg() = default;

    MinionDmg(int hp, sf::Font &font, const std::string &textureString, sf::Vector2f size,
              const std::string &attackerTxtrString, int attackDamage_, int damageOnDeath_);

    Minion *clone() const override;

    void onDeathSpell(std::vector<Minion *> &allyUnits, std::vector<Minion *> &enemyUnits) override;
};


#endif //OOP_MINIONDMG_H
