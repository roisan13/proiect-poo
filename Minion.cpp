//
// Created by Radu on 5/12/2024.
//

#include "Minion.h"

Minion::Minion(int hp, sf::Font &font, const std::string &textureString, sf::Vector2f size,
               const std::string &attackerTxtrString, int attackDamage_) :
        pveVoievod(hp, font, textureString, size, attackerTxtrString), attackDamage(attackDamage_) {
    adText.setFont(font);
    adText.setString(std::to_string(attackDamage_));
    adText.setCharacterSize(36);
    adText.setFillColor(sf::Color::White);
}

bool Minion::attackEnemy(pveVoievod *target) {
    if (!hasAttacked) {
        std::cout << "Se ataca acum cu: " << attackDamage << "damage! \n";
        target->loseHealth(attackDamage);
        // std::cout << target->healthPoints << "\n";
        hasAttacked = true;
        return true;
    }
    return false;
}

void Minion::setPosition(sf::Vector2f pos) {
    icon.setPosition(pos);

    // center text?!
    float xPos = pos.x + icon.getSize().x - 60;
    float yPos = pos.y + icon.getSize().y - 60;

    hpText.setPosition({xPos, yPos});
    xPos = pos.x + 35;
    adText.setPosition({xPos, yPos});
}

sf::RectangleShape Minion::getTargetOverlay() {
    sf::RectangleShape targetOverlay;

    targetOverlay.setPosition({icon.getPosition().x + 25, icon.getPosition().y + 21});

    targetOverlay.setSize({icon.getSize().x - 50, icon.getSize().y - 50});

    return targetOverlay;
}

void Minion::drawTo(sf::RenderWindow &window) {
    window.draw(icon);
    window.draw(hpText);
    window.draw(adText);
}

bool Minion::hasAttackedEnemy() const {
    return hasAttacked;
}

void Minion::refreshAttack() {
    hasAttacked = false;
}
