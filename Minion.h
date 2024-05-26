//
// Created by Radu on 5/12/2024.
//

#ifndef OOP_MINION_H
#define OOP_MINION_H

#include "pveVoievod.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class Minion : public pveVoievod {
private:
    int attackDamage;
    bool hasAttacked = false;
    sf::Text adText;

protected:
    Minion(const Minion &other) = default;

    Minion &operator=(const Minion &other) = default;

public:

    Minion(int hp, sf::Font &font, const std::string &textureString, sf::Vector2f size,
           const std::string &attackerTxtrString, int attackDamage_);

    virtual void onDeathSpell(std::vector<Minion *> allyUnits, std::vector<Minion *> enemyUnits) = 0;

    virtual Minion *clone() const = 0;

    bool attackEnemy(pveVoievod *target);

    void setPosition(sf::Vector2f pos) override;

    sf::RectangleShape getTargetOverlay() override;

    void drawTo(sf::RenderWindow &window) override;

    void refreshAttack();

    bool hasAttackedEnemy() const;
};


#endif //OOP_MINION_H
