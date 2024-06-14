//
// Created by Radu on 6/11/2024.
//

#include "Minion_Builder.h"

Minion_Builder &Minion_Builder::health(int val) {
    otoman.healthPoints = val;
    otoman.hpText.setString(std::to_string(otoman.healthPoints));

    return *this;
}

Minion_Builder &Minion_Builder::font(sf::Font &font) {
    otoman.hpText.setFont(font);
    otoman.hpText.setCharacterSize(36);
    otoman.hpText.setFillColor(sf::Color::White);

    otoman.adText.setFont(font);
    otoman.adText.setCharacterSize(36);
    otoman.adText.setFillColor(sf::Color::White);

    return *this;
}

Minion_Builder &Minion_Builder::texture(const std::string &textureString) {
    if (!otoman.voievodTexture.loadFromFile(textureString))
        throw attributeError();

    return *this;
}

Minion_Builder &Minion_Builder::attackerTexture(const std::string &attackerTxtrString) {
    if (!otoman.attackerTexture.loadFromFile(attackerTxtrString))
        throw attributeError();

    return *this;
}

Minion_Builder &Minion_Builder::size(sf::Vector2f size_) {
    otoman.size = size_;
    otoman.icon.setSize(size_);
    otoman.increasedSize = {otoman.size.x + otoman.sizeIncrease, otoman.size.y + otoman.sizeIncrease};

    return *this;
}

Minion_Builder &Minion_Builder::attackDamage(int attackDamage_) {
    otoman.attackDamage = attackDamage_;
    otoman.adText.setString(std::to_string(otoman.attackDamage));

    return *this;

}

Minion_Builder &Minion_Builder::damageOnDeath(int damageOnDeath_) {
    otoman.damageOnDeath = damageOnDeath_;
    return *this;
}

MinionDmg Minion_Builder::build() {
    auto temp = otoman;
    otoman = MinionDmg();
    return temp;
}
