//
// Created by Radu on 5/12/2024.
//

#ifndef OOP_PVEVOIEVOD_H
#define OOP_PVEVOIEVOD_H


#include "Exceptions.h"
#include <SFML/Graphics.hpp>

class pveVoievod {
protected:
    sf::Vector2f size, position, increasedSize;
    float sizeIncrease = 10.f;
    bool isIncreased = false;
    bool markedForRemoval = false;
    int healthPoints = 0;
    sf::RectangleShape icon;
    sf::Text hpText;
    sf::Texture voievodTexture, attackerTexture;


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

    void highlightAsAttacker();

    void un_highlight();

    void restoreOriginalSize();

    virtual sf::RectangleShape getTargetOverlay();

    void markForRemoval();

    bool hasBeenMarked() const;

};


#endif //OOP_PVEVOIEVOD_H
