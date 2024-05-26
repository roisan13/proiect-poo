//
// Created by Radu on 5/26/2024.
//

#include "MinionHeal.h"

MinionHeal::MinionHeal(int hp, sf::Font &font, const std::string &textureString, sf::Vector2f size,
                       const std::string &attackerTxtrString, int attackDamage_, int healOnDeath_) :
        Minion(hp, font, textureString, size, attackerTxtrString, attackDamage_), healOnDeath(healOnDeath_) {
    if (healOnDeath_ < 0)
        throw attributeError("MinionHeal");
}

Minion *MinionHeal::clone() const {
    return new MinionHeal(*this);
}

void MinionHeal::onDeathSpell(std::vector<Minion *> allyUnits, std::vector<Minion *> enemyUnits) {
    for (auto &enemyUnit: enemyUnits)
        enemyUnit->gainHealth(healOnDeath);
}
