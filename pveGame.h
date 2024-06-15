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
#include "Minion_Factory.h"
#include "Minion_Builder.h"
#include "SingletonGame.h"
#include "random.hpp"
#include <queue>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class pveGame : public SingletonGame<pveGame> {

private:
    sf::Texture bgTexture;
    sf::Texture voievodTexture, otomanTexture;
    sf::Sprite bgSprite;
    sf::RectangleShape targetOverlay;
    sf::Vector2f iconSize = {200.f, 200.f};

    sf::Font fontAr;
    Button endTurnButton;
    pveVoievod voievod, otoman;
    std::vector<Minion *> voievodMinions, otomanMinions;
    Minion *attacker = nullptr;
    std::queue<Minion *> dyingMinions;
    Minion *deadMinion = nullptr;


    float yPosOtomanUnit = 0.f, yPosVoievodUnit = 0.f;
    bool isPlayerTurn = true;
    bool isDmgAnimationPlaying = false;
    bool animationDmgPlayedOnce = false;
    bool isDeathAnimationPlaying = false;
    int clrAlpha = 255;


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

    static void getRandomValues(int &hp, int &ad, int &deathDmg);

protected:
    pveGame() = default;

public:

    ~pveGame();

    pveVoievod *checkUnitClick(const std::vector<Minion *> &units, sf::RenderWindow &window);

    void checkHovers(sf::RenderWindow &window);

    void checkMouseClick(sf::RenderWindow &window);

    void showOverlayOver(pveVoievod *target);

    void findTargetAndAttack(pveVoievod *selected);

    void checkMouseClickForAttack(sf::RenderWindow &window);

    void event_polling(sf::RenderWindow &window);

    void computer_event_polling();

    void addToDeathChain();

    void removeFromDeathChainAndDelete();

    void nextInDeathChain();

    void drawMinions(sf::RenderWindow &window);

    void render(sf::RenderWindow &window);

    void animate();

    void gameOver();

    void play();

    template<typename T> friend
    class SingletonGame;
};


#endif //OOP_PVEGAME_H
