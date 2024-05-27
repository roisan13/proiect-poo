//
// Created by Radu on 5/27/2024.
//

#include "MinionDmgHeal.h"

MinionDmgHeal::MinionDmgHeal(int hp, sf::Font &font, const std::string &textureString, sf::Vector2f size,
                             const std::string &attackerTxtrString, int attackDamage_, int damageOnDeath_,
                             int healOnDeath_) :
        Minion(hp, font, textureString, size, attackerTxtrString, attackDamage_), damageOnDeath(damageOnDeath_),
        healOnDeath(healOnDeath_) {}

void MinionDmgHeal::onDeathSpell(std::vector<Minion *> &allyUnits, std::vector<Minion *> &enemyUnits) {
    for (auto &enemyUnit: enemyUnits)
        enemyUnit->loseHealth(damageOnDeath);

    for (auto &allyUnit: allyUnits)
        if (allyUnit != this)
            allyUnit->gainHealth(healOnDeath);
}

Minion *MinionDmgHeal::clone() const {
    return new MinionDmgHeal(*this);
}