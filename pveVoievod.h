//
// Created by Radu on 5/12/2024.
//

#ifndef OOP_PVEVOIEVOD_H
#define OOP_PVEVOIEVOD_H


#include "Exceptions.h"
#include <SFML/Graphics.hpp>

class pveVoievod {
private:


    sf::Vector2f size, position, increasedSize;
    float sizeIncrease = 10.f;
    bool isIncreased = false;
    sf::Texture voievodTexture, attackerTexture;
protected:
    int healthPoints = 0;
    sf::RectangleShape icon;
    sf::Text hpText;


public:
    pveVoievod(int hp, sf::Font &font, const std::string &textureString, sf::Vector2f size_,
               const std::string &attackerTxtrString);

    pveVoievod(int hp, sf::Font &font, const sf::Texture &texture, sf::Vector2f size_);

    pveVoievod() = default;

    virtual ~pveVoievod() = default;

    virtual void setPosition(sf::Vector2f pos);

    void loseHealth(int damageDealt);

    void gainHealth(int healthGained);

    virtual void drawTo(sf::RenderWindow &window);

    bool isHovered(sf::RenderWindow &window);

    bool isAlive() const;

    void increaseSize();

    void highlightAsAttacker() {
        icon.setTexture(&attackerTexture);
    }

    void un_highlight() {
        icon.setTexture(&voievodTexture);
    }

    void restoreOriginalSize() {
        if (isIncreased) {
            icon.setPosition({icon.getPosition().x + sizeIncrease / 2, icon.getPosition().y + sizeIncrease / 2});
            icon.setSize(size);
            isIncreased = false;
        }
    }

    virtual sf::RectangleShape getTargetOverlay() {
        sf::RectangleShape targetOverlay;

        targetOverlay.setPosition(icon.getPosition());

        targetOverlay.setSize(icon.getSize());


        return targetOverlay;
    }

};


#endif //OOP_PVEVOIEVOD_H
