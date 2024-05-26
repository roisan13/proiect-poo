//
// Created by Radu on 5/26/2024.
//

#include "MinionDmgAll.h"

MinionDmgAll::MinionDmgAll(int hp, sf::Font &font, const std::string &textureString, sf::Vector2f size,
                           const std::string &attackerTxtrString, int attackDamage_, int damageOnDeath_) :
        Minion(hp, font, textureString, size, attackerTxtrString, attackDamage_), damageOnDeath(damageOnDeath_) {}

void MinionDmgAll::onDeathSpell(std::vector<Minion *> &allyUnits, std::vector<Minion *> &enemyUnits) {
    for (auto &enemyUnit: enemyUnits)
        enemyUnit->loseHealth(damageOnDeath);

    for (auto &allyUnit: allyUnits)
        allyUnit->loseHealth(damageOnDeath);
}

Minion *MinionDmgAll::clone() const {
    return new MinionDmgAll(*this);
}
