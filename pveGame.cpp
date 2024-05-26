//
// Created by Radu on 5/12/2024.
//

#include "pveGame.h"

void pveGame::init_voievozi() {

    sf::Vector2f pveVoievodSize = {180.f, 180.f};
    voievod = pveVoievod(10, fontAr, voievodTexture, pveVoievodSize);
    otoman = pveVoievod(10, fontAr, otomanTexture, pveVoievodSize);

    otoman.setPosition({550.f, 20.f});
    voievod.setPosition({550.f, 700.f});
}

void pveGame::init_sprites() {
    bgTexture.loadFromFile("sprites/pvebg.png");
    bgSprite.setTexture(bgTexture);

    voievodTexture.loadFromFile("sprites/mihai.jpg");
    otomanTexture.loadFromFile("sprites/sinan.jpg");

    fontAr.loadFromFile("sprites/arial.ttf");
}

void pveGame::init_buttons() {
    endTurnButton = Button("END TURN", fontAr, {180.f, 60.f}, sf::Color(90, 150, 30));
    //
    endTurnButton.setPosition({1080.f, 420.f});
}

void pveGame::init_minions() {


    auto raduBuzescu = MinionDmgAll(10, fontAr, "sprites/radu.png", iconSize, "sprites/raduAttacker.png", 2, 3);
    auto popa = MinionHeal(13, fontAr, "sprites/popa.png", iconSize, "sprites/popaAttacker.png", 2, 3);
    auto predaBuzescu = MinionDmg(11, fontAr, "sprites/preda.png", iconSize, "sprites/predaAttacker.png", 3, 3);
    auto stroeBuzescu = MinionDmg(8, fontAr, "sprites/stroe.png", iconSize, "sprites/stroeAttacker.png", 2, 1);

    voievodMinions.push_back(raduBuzescu.clone());
    voievodMinions.push_back(popa.clone());
    voievodMinions.push_back(predaBuzescu.clone());
    voievodMinions.push_back(stroeBuzescu.clone());

    auto pasa1 = MinionDmg(11, fontAr, "sprites/pasa1.png", iconSize, "sprites/pasa1Attacker.png", 2, 2);
    auto pasa2 = MinionDmg(13, fontAr, "sprites/pasa2.png", iconSize, "sprites/pasa2Attacker.png", 3, 2);
    auto pasa3 = MinionDmg(9, fontAr, "sprites/pasa3.png", iconSize, "sprites/pasa3Attacker.png", 4, 2);
    auto pasa4 = MinionDmg(11, fontAr, "sprites/pasa4.png", iconSize, "sprites/pasa4Attacker.png", 3, 2);
    auto pasa5 = MinionDmg(9, fontAr, "sprites/pasa5.png", iconSize, "sprites/pasa5Attacker.png", 4, 2);

    otomanMinions.push_back(pasa1.clone());
    otomanMinions.push_back(pasa2.clone());
    otomanMinions.push_back(pasa3.clone());
    otomanMinions.push_back(pasa4.clone());
    // otomanMinions.push_back(pasa5.clone());


    // magic number 225 = screenHeight(900) / 4
    yPosVoievodUnit = 475.f;
    yPosOtomanUnit = 225.f;
    for (auto unit: voievodMinions)
        unit->un_highlight();
    for (auto unit: otomanMinions)
        unit->un_highlight();
    setUnitsPos(voievodMinions, false);
    setUnitsPos(otomanMinions, true);


}

void pveGame::setUnitsPos(std::vector<Minion *> &units, bool isOtoman) {
    /// CENTER and JUSTIFY minion icons
    int iconSide = 200;
    int gap = 25, screenWidth = 1280;
    int n = int(units.size());
    int xPos = (screenWidth - n * (iconSide) - (n - 1) * gap) / 2;
    float yPos;

    if (isOtoman)
        yPos = yPosOtomanUnit;
    else yPos = yPosVoievodUnit;

    std::cout << "Pt setUnitsPos, n = " << n << "\n";
    std::cout << "Pt otomanUnits, n = " << otomanMinions.size() << "\n";

    for (auto unit: units) {
        unit->setPosition({static_cast<float>(xPos), yPos});
        xPos += iconSide + gap;
    }

}

void pveGame::checkUnitHovers(std::vector<Minion *> &units, sf::RenderWindow &window) {
    for (auto &unit: units)
        if (unit->isHovered(window)) {
//                std::cout << "hover pe minion!\n";
            unit->increaseSize();
        } else {
            unit->restoreOriginalSize();
        }

}

void pveGame::checkOtomanHover(sf::RenderWindow &window) {
    if (otoman.isHovered(window))
        otoman.increaseSize();
    else otoman.restoreOriginalSize();
}

void pveGame::checkButtonHover(sf::RenderWindow &window) {
    if (isPlayerTurn) {
        if (endTurnButton.isHovered(window)) {
            endTurnButton.setBackColor(sf::Color(114, 207, 21));
        } else endTurnButton.setBackColor(sf::Color(90, 150, 30));
    }
}

void pveGame::refreshMinionAttack(std::vector<Minion *> &units) {
    for (auto unit: units)
        unit->refreshAttack();
}

void pveGame::changeTurn() {
    if (isPlayerTurn) {
        endTurnButton.setBackColor(sf::Color(46, 46, 46));
        endTurnButton.setTextString("ENEMY TURN");

        refreshMinionAttack(voievodMinions);
        isPlayerTurn = false;

        attacker = nullptr;
    } else {

        endTurnButton.setBackColor(sf::Color(90, 150, 30));
        endTurnButton.setTextString("END TURN");

        refreshMinionAttack(otomanMinions);
        isPlayerTurn = true;
        attacker = nullptr;
    }
}

void pveGame::checkButtonClick(sf::RenderWindow &window) {
    if (endTurnButton.isHovered(window) && isPlayerTurn) {
        endTurnButton.setBackColor(sf::Color(46, 46, 46));
        endTurnButton.setTextString("ENEMY TURN");

        refreshMinionAttack(voievodMinions);
        isPlayerTurn = false;

        attacker = nullptr;
    }
}

Minion *pveGame::computer_chooseAttacker() {
    for (auto otomanMinion: otomanMinions) {
        if (!otomanMinion->hasAttackedEnemy())
            return otomanMinion;
    }

    changeTurn();
    return nullptr;
}

pveVoievod *pveGame::computer_chooseTarget() {
    if (!voievodMinions.empty())
        return voievodMinions[0];
    else return &voievod;
}

pveVoievod *pveGame::checkUnitClick(std::vector<Minion *> &units, sf::RenderWindow &window) {
    for (auto unit: units) {
        if (unit->isHovered(window))
            return unit;
    }

    if (voievod.isHovered(window))
        return &voievod;
    if (otoman.isHovered(window))
        return &otoman;
    return nullptr;
}

void pveGame::checkForAliveResize(std::vector<Minion *> &units, bool isOtoman) {
    // isOtoman = false   < == >   se sterge (a murit) un minion OTOMAN

    bool hasErased = false;
    for (auto unit = units.begin(); unit != units.end(); ++unit) {
        if (!(*unit)->isAlive()) {
            hasErased = true;
            units.erase(unit);
            break;
        }
    }

    if (hasErased) {
        setUnitsPos(units, isOtoman);
    }
}

void pveGame::checkHovers(sf::RenderWindow &window) {
    if (!isAnimationPlaying) {
        checkUnitHovers(voievodMinions, window);
        checkUnitHovers(otomanMinions, window);   // Hover over enemies to select target

        checkOtomanHover(window);  // Hover over enemy pveVoievod (can't click him if he has minions)
        checkButtonHover(window);
    }

}

void pveGame::checkMouseClick(sf::RenderWindow &window) {
    if (!isAnimationPlaying) {
        checkButtonClick(window);
        checkMouseClickForAttack(window);
    }
}

void pveGame::showOverlayOver(pveVoievod *target) {
    targetOverlay = target->getTargetOverlay();
    if (targetOverlay.getPosition() == sf::Vector2f({0, 0}))
        throw grahicsError();
    isAnimationPlaying = true;
    clrAlpha = 255;
}

void pveGame::findTargetAndAttack(pveVoievod *selected) {
    if (auto target = dynamic_cast<Minion *>(selected)) {
        /// Atack a minion
        std::cout << "Attacker HAS Attacked TARGET!\n";

        if (!target->isAlive())
            throw gameLogicError();

        if (attacker->attackEnemy(target)) {
            target->restoreOriginalSize();
            showOverlayOver(target);
        }
        if (!target->isAlive())
            target->onDeathSpell(otomanMinions, voievodMinions);

    }
    if (auto target = selected) {
        /// Attack a voievod
        if ((target == &voievod && voievodMinions.empty()) || (target == &otoman && otomanMinions.empty())) {
            if (attacker->attackEnemy(target)) {
                target->restoreOriginalSize();
                showOverlayOver(target);
            }
            std::cout << "pveVoievod attacks pveVoievod\n";
        }
    }
    if (isPlayerTurn) {
        attacker->un_highlight();
        attacker = nullptr;
    }
}

void pveGame::checkMouseClickForAttack(sf::RenderWindow &window) {
    if (attacker == nullptr) {
        attacker = dynamic_cast<Minion *>(checkUnitClick(voievodMinions, window));
        if (attacker) {
            std::cout << "Attacker HAS BEEN SELECTED!\n";
            attacker->highlightAsAttacker();
        }

    } else {
        findTargetAndAttack(checkUnitClick(otomanMinions, window));
    }
}

void pveGame::event_polling(sf::RenderWindow &window) {
    sf::Event ev{};

    //Event polling
    while (window.pollEvent(ev)) {

        switch (ev.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (ev.key.code == sf::Keyboard::Escape)
                    window.close();
                break;
            case sf::Event::MouseMoved:
                checkHovers(window);
                break;
            case sf::Event::MouseButtonPressed:
                checkMouseClick(window);

            default:
                break;
        }
    }

}

void pveGame::computer_event_polling() {

    if (!(isPlayerTurn || isAnimationPlaying)) {
        if (attacker == nullptr) {
            attacker = computer_chooseAttacker();
            if (attacker) {
                std::cout << "Computer has SELECTED Attacker!\n";
                attacker->highlightAsAttacker();
            }

            if (attacker == &voievod && !voievodMinions.empty())
                throw gameLogicError();
        } else {
            findTargetAndAttack(computer_chooseTarget());
        }
    }

}

void pveGame::drawMinions(sf::RenderWindow &window) {
    for (auto voievodMinion: voievodMinions)
        voievodMinion->drawTo(window);

    for (auto otomanMinion: otomanMinions)
        otomanMinion->drawTo(window);
}

void pveGame::render(sf::RenderWindow &window) {
    window.clear(sf::Color::Black); //Clear old frame

    window.draw(bgSprite);
    voievod.drawTo(window);
    otoman.drawTo(window);

    drawMinions(window);
    endTurnButton.drawTo(window);


    window.draw(targetOverlay);

    // window.draw(spriteV2);
    // window.draw(nenorociri);

}

void pveGame::animate() {

    if (isAnimationPlaying) {
        targetOverlay.setFillColor(sf::Color(255, 0, 0, clrAlpha));
        clrAlpha -= 7;
        if (clrAlpha < 0 && !animationPlayedOnce) {
            clrAlpha = 255;
            animationPlayedOnce = true;
        } else if (clrAlpha < 0 && animationPlayedOnce) {
            clrAlpha = 0;
            animationPlayedOnce = false;
            isAnimationPlaying = false;

            if (!isPlayerTurn) {
                attacker->un_highlight();
                attacker = nullptr;
            }

            checkForAliveResize(voievodMinions, false);
            checkForAliveResize(otomanMinions, true);
        }
    }
}

void pveGame::gameOver() {
    sf::RenderWindow window(sf::VideoMode(1280, 900), "Game over");

    window.setVerticalSyncEnabled(true);
    sf::Sprite bg;
    sf::Texture bgtxt;
    if (voievod.isAlive())
        bgtxt.loadFromFile("sprites/gameWon.png");
    else bgtxt.loadFromFile("sprites/gameLost.png");

    bg.setTexture(bgtxt);
    bg.setPosition({0, 0});
    while (window.isOpen()) {
        sf::Event ev{};

        //Event polling
        while (window.pollEvent(ev)) {
            switch (ev.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }
        window.draw(bg);
        window.display();
    }
}

void pveGame::play() {
    sf::RenderWindow window(sf::VideoMode(1280, 900), "Voievod vs Otoman");

    /// Do NOT burn the GPU.
    window.setVerticalSyncEnabled(true);

    init_sprites();
    init_voievozi();
    init_minions();
    init_buttons();

    while (window.isOpen() && voievod.isAlive() && otoman.isAlive()) {
        // Get PLAYER input
        event_polling(window);

        // Get COMPUTER input
        computer_event_polling();

        // Draw any animation playing
        animate();

        //Render
        render(window);

        //Draw your game
        window.display(); //Tell app that window is done drawing

    }
    window.close();
    if (voievod.isAlive() == !otoman.isAlive())
        gameOver();
}
