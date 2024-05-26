//
// Created by Radu on 5/14/2024.
//

#include "MinionDmg.h"

Minion *MinionDmg::clone() const {
    return new MinionDmg(*this);
}

void MinionDmg::onDeathSpell(std::vector<Minion *> allyUnits, std::vector<Minion *> enemyUnits) {
    for (auto &enemyUnit: enemyUnits)
        enemyUnit->loseHealth(damageOnDeath);
}

MinionDmg::MinionDmg(int hp, sf::Font &font, const std::string &textureString, sf::Vector2f size,
                     const std::string &attackerTxtrString, int attackDamage_, int damageOnDeath_) :
        Minion(hp, font, textureString, size, attackerTxtrString, attackDamage_), damageOnDeath(damageOnDeath_) {}
