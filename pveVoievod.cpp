//
// Created by Radu on 5/12/2024.
//

#include "pveVoievod.h"

pveVoievod::pveVoievod(int hp, sf::Font &font, const std::string &textureString, sf::Vector2f size_,
                       const std::string &attackerTxtrString) {
    healthPoints = hp;

    hpText.setFont(font);
    hpText.setString(std::to_string(healthPoints));
    hpText.setCharacterSize(36);
    hpText.setFillColor(sf::Color::White);

    size = size_;
    increasedSize = {size.x + sizeIncrease, size.y + sizeIncrease};
    icon.setSize(size_);
    // icon.setTexture(&texture);


    if (!voievodTexture.loadFromFile(textureString))
        throw attributeError();
    if (!attackerTexture.loadFromFile(attackerTxtrString))
        throw attributeError();
}

pveVoievod::pveVoievod(int hp, sf::Font &font, const sf::Texture &texture, sf::Vector2f size_) {
    healthPoints = hp;

    hpText.setFont(font);
    hpText.setString(std::to_string(healthPoints));
    hpText.setCharacterSize(36);
    hpText.setFillColor(sf::Color::Black);

    size = size_;
    increasedSize = {size.x + sizeIncrease, size.y + sizeIncrease};
    icon.setSize(size_);
    icon.setTexture(&texture);
    voievodTexture = texture;
}

void pveVoievod::setPosition(sf::Vector2f pos) {
    icon.setPosition(pos);

    // center text?!
    float xPos = pos.x + icon.getSize().x - 60;
    float yPos = pos.y + icon.getSize().y - 60;

    hpText.setPosition({xPos, yPos});
}

void pveVoievod::loseHealth(int damageDealt) {
    healthPoints -= damageDealt;

    // Update HP text
    hpText.setString(std::to_string(healthPoints));
}

void pveVoievod::gainHealth(int healthGained) {
    healthPoints += healthGained;

    // Update HP text
    hpText.setString(std::to_string(healthPoints));
}

void pveVoievod::drawTo(sf::RenderWindow &window) {
    window.draw(icon);
    window.draw(hpText);
}

bool pveVoievod::isHovered(sf::RenderWindow &window) {
    float mouseX = float(sf::Mouse::getPosition(window).x);
    float mouseY = float(sf::Mouse::getPosition(window).y);

    float icnPosX = icon.getPosition().x;
    float icnPosY = icon.getPosition().y;
    float icnRightMargin = icnPosX + icon.getLocalBounds().width;
    float icnDownMargin = icnPosY + icon.getLocalBounds().height;

    return (mouseX < icnRightMargin && mouseX > icnPosX && mouseY < icnDownMargin && mouseY > icnPosY);
}

bool pveVoievod::isAlive() const {
    return healthPoints > 0;
}

void pveVoievod::increaseSize() {
    if (!isIncreased) {
        icon.setSize(increasedSize);
        icon.setPosition({icon.getPosition().x - sizeIncrease / 2, icon.getPosition().y - sizeIncrease / 2});
        isIncreased = true;
    }
}
