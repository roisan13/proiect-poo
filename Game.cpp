//
// Created by Radu on 4/24/2024.
//

#include "Game.h"

void Game::init_voievodtextHP() {
    textHP1.setFont(fontAr);
    textHP2.setFont(fontAr);
    textHP1.setCharacterSize(72);
    textHP2.setCharacterSize(72);
    textHP1.setPosition({600.f, 350.f});
    textHP2.setPosition({600.f, 800.f});
    voievod1.updateHPText(textHP1);
    voievod2.updateHPText(textHP2);
}

void Game::init_sprites() {
    // Load the textures for the background
    textureV1.loadFromFile("sprites/MichaelTheBrave.png");
    textureV2.loadFromFile("sprites/VladTheImpaler.png");
    spriteV1.setTexture(textureV1);
    spriteV2.setTexture(textureV2);
    spriteV2.setPosition(0, 450);

    fontAr.loadFromFile("sprites/arial.ttf");
}

void Game::init_alertText() {
    alertText.setFont(fontAr);
    alertText.setCharacterSize(60);
    alertText.setFillColor(sf::Color::Red);
    alertText.setString("Alert TEXT!");
}

void Game::init_voievodButtons() {

    // Buttons for voievod1
    btn1V1 = Button("Basic Attack", fontAr, {400, 50}, sf::Color::Black);
    btn2V1 = Button("Powerful Attack", fontAr, {400, 50}, sf::Color::Black);
    btn3V1 = Button("Battle of Călugăreni", fontAr, {400, 50}, sf::Color::Black);
    btn1V1.setPosition({20.f, 25.f});
    btn2V1.setPosition({20.f, 100.f});
    btn3V1.setPosition({20.f, 175.f});
    v1buttons = {btn1V1, btn2V1, btn3V1};


    // Buttons for voievod2
    btn1V2 = Button("Basic Attack", fontAr, {400, 50}, sf::Color::Black);
    btn2V2 = Button("Powerful Attack", fontAr, {400, 50}, sf::Color::Black);
    btn3V2 = Button("Night Attack at Târgoviște", fontAr, {400, 50}, sf::Color::Black);

    // de schimbat numerele astea magice la un moment dat!
    btn1V2.setPosition({20.f, 450.f + 25.f});
    btn2V2.setPosition({20.f, 450.f + 100.f});
    btn3V2.setPosition({20.f, 450.f + 175.f});
    v2buttons = {btn1V2, btn2V2, btn3V2};
}


Game::~Game() {
    std::cout << "\n Game destructor \n";
}

void Game::mouseAction(sf::RenderWindow &window, std::vector<Button> buttons, Voievod &voievod, Voievod &voievodAtacat,
                       sf::Text &textHPvoievodAtacat) {
    for (unsigned int i = 0; i < buttons.size(); ++i)
        if (buttons[i].isHovered(window)) {
            /// CHECK IF IT IS CORRECT ROUND!!!
            /// PLAY AUDIO!!!!
            voievod.useSpell(i, voievodAtacat, alertString);
            voievodAtacat.updateHPText(textHPvoievodAtacat);

            alertTextShowing = true;
            alertText.setString(alertString);
            if (gameState == 1)
                gameState = 2;
            else if (gameState == 2)
                gameState = 1;
        }
}

void Game::checkMouseButtonPressed(sf::RenderWindow &window) {
    if (gameState == 1) {
        mouseAction(window, v1buttons, voievod1, voievod2, textHP2);

    } else if (gameState == 2) {
        mouseAction(window, v2buttons, voievod2, voievod1, textHP1);
    }
}

void Game::event_polling(sf::RenderWindow &window) {
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
                for (auto &v1button: v1buttons)
                    if (v1button.isHovered(window)) {
                        v1button.setBackColor(sf::Color::Red);
                    } else {
                        v1button.setBackColor(sf::Color::Black);
                    }
                for (auto &v2button: v2buttons)
                    if (v2button.isHovered(window)) {
                        v2button.setBackColor(sf::Color::Red);
                    } else {
                        v2button.setBackColor(sf::Color::Black);
                    }
                break;
            case sf::Event::MouseButtonPressed:
                std::cout << " Buton mouse apasat\n";
                checkMouseButtonPressed(window);


            default:
                break;
        }
    }

}

void Game::renderGame(sf::RenderWindow &window) {

    window.clear(sf::Color::Black); //Clear old frame

    if (alertTextShowing) {
        clrAlpha = 255;
        alertTextShowing = false;
        alertText.setPosition({800.f, 450.f});
    }

    if (clrAlpha > 0) {
        alertText.setFillColor(sf::Color(255, 0, 0, clrAlpha));
        clrAlpha -= 2;
        alertText.move(0.f, -1.f);
    }

    window.draw(spriteV1);
    window.draw(spriteV2);
    window.draw(textHP1);
    window.draw(textHP2);
    if (clrAlpha > 0)
        window.draw(alertText);

    for (auto &button: v1buttons)
        button.drawTo(window);
    for (auto &button: v2buttons)
        button.drawTo(window);
}

void Game::play() {
    sf::RenderWindow window(sf::VideoMode(1280, 900), "Voievozi vs Voievod");

    /// Do NOT burn the GPU.
    window.setVerticalSyncEnabled(true);

    init_voievozi();
    init_sprites();
    init_voievodtextHP();
    init_alertText();
    init_voievodButtons();

    while (window.isOpen() && voievod1.isAlive() && voievod2.isAlive()) {
        event_polling(window);

        //Render
        renderGame(window);

        //Draw your game
        window.display(); //Tell app that window is done drawing

        if (!(voievod1.isAlive() && voievod2.isAlive())) {
            gameState = 0;
        }

    }

    displayWinner();
}

void Game::displayWinner() {
    sf::RenderWindow window(sf::VideoMode(1280, 900), "Game over");

    window.setVerticalSyncEnabled(true);
    sf::Sprite bg;
    sf::Texture bgtxt;
    if (voievod1.isAlive())
        bgtxt.loadFromFile("sprites/michaelwins.png");
    else {
        bgtxt.loadFromFile("sprites/vladwins.png");
    }

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

void Game::init_voievozi() {
    std::string specialAttackText = "Battle of Călugăreni";
    sf::String sfTmp = sf::String::fromUtf8(specialAttackText.begin(), specialAttackText.end());
    Spell basicAttack = Spell("Basic Attack", 5, 30, 85);
    Spell powerfulAttack = Spell("Powerful Attack", 10, 20, 60);
    Spell voievod1specificAttack = Spell("Battle of Călugăreni", 15, 20, 25);

    Spell voievod2specificAttack = Spell("Battle of Târgoviște", 15, 20, 25);

    voievod1 = Voievod("Michael The Brave", 89, 30, {basicAttack, powerfulAttack, voievod1specificAttack});
    voievod2 = Voievod("Vlad The Impaler", 93, 30, {basicAttack, powerfulAttack, voievod2specificAttack});
}
