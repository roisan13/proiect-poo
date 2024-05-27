//
// Created by Radu on 5/12/2024.
//

#ifndef OOP_PVEGAME_H
#define OOP_PVEGAME_H


#include <iostream>
#include "pveVoievod.h"
#include "Minion.h"
#include "Button.h"
#include "Exceptions.h"
#include "MinionDmg.h"
#include "MinionHeal.h"
#include "MinionDmgAll.h"
#include "MinionDmgHeal.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class pveGame {
private:
    sf::Texture bgTexture, voievodTexture, otomanTexture, babanovacTexture, hasanpasaTexture;
    sf::Sprite bgSprite;
    sf::RectangleShape targetOverlay;
    sf::Vector2f iconSize = {200.f, 200.f};

    sf::Font fontAr;
    Button endTurnButton;
    pveVoievod voievod, otoman;
    std::vector<Minion *> voievodMinions, otomanMinions;
    Minion *attacker = nullptr;


    float yPosOtomanUnit = 0.f, yPosVoievodUnit = 0.f;
    bool isPlayerTurn = true, isAnimationPlaying = false, animationPlayedOnce = false;
    int clrAlpha = 255;

private:

    void init_voievozi();

    void init_sprites();

    void init_buttons();

    void init_minions();

    void setUnitsPos(std::vector<Minion *> &units, bool isOtoman = false);

    static void checkUnitHovers(std::vector<Minion *> &units, sf::RenderWindow &window);

    void checkOtomanHover(sf::RenderWindow &window);

    void checkButtonHover(sf::RenderWindow &window);

    static void refreshMinionAttack(const std::vector<Minion *> &units);

    void changeTurn();

    void checkButtonClick(sf::RenderWindow &window);

    Minion *computer_chooseAttacker();

    pveVoievod *computer_chooseTarget();


public:
    pveGame() = default;

    ~pveGame() = default;

    pveVoievod *checkUnitClick(const std::vector<Minion *> &units, sf::RenderWindow &window);

    void checkForAliveResize(std::vector<Minion *> &units, bool isOtoman);

    void checkHovers(sf::RenderWindow &window);

    void checkMouseClick(sf::RenderWindow &window);

    void showOverlayOver(pveVoievod *target);

    void findTargetAndAttack(pveVoievod *selected);

    void checkMouseClickForAttack(sf::RenderWindow &window);

    void event_polling(sf::RenderWindow &window);

    void computer_event_polling();

    void drawMinions(sf::RenderWindow &window);

    void render(sf::RenderWindow &window);

    void animate();

    void gameOver();

    void play();
};


#endif //OOP_PVEGAME_H
