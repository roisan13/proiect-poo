//
// Created by Radu on 5/26/2024.
//

#include "Minion.h"

#ifndef OOP_MINIONDMGALL_H
#define OOP_MINIONDMGALL_H


class MinionDmgAll : public Minion {
private:
    int damageOnDeath;
public:
    MinionDmgAll(int hp, sf::Font &font, const std::string &textureString, sf::Vector2f size,
                 const std::string &attackerTxtrString, int attackDamage_, int damageOnDeath_);

    Minion *clone() const override;

    void onDeathSpell(std::vector<Minion *> allyUnits, std::vector<Minion *> enemyUnits) override;
};

#endif //OOP_MINIONDMGALL_H
