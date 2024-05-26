//
// Created by Radu on 4/24/2024.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H

#include "Voievod.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>


class Game {
private:
    Voievod voievod1, voievod2;

    sf::Sprite spriteV1, spriteV2;
    sf::Texture textureV1, textureV2;
    sf::Font fontAr;
    sf::Text textHP1, textHP2;
    sf::Text alertText;
    Button btn1V1, btn2V1, btn3V1, btn1V2, btn2V2, btn3V2;
    std::vector<Button> v1buttons, v2buttons;
    unsigned int gameState;
    int clrAlpha;
    bool alertTextShowing;
    std::string alertString;

    void init_voievodtextHP();

    void init_sprites();

    void init_alertText();

    void init_voievodButtons();


public:

    Game(const Voievod &voievod1, const Voievod &voievod2);

    ~Game();

    void mouseAction(sf::RenderWindow &window, std::vector<Button> buttons, Voievod &voievod, Voievod &voievodAtacat,
                     sf::Text &textHPvoievodAtacat);

    void checkMouseButtonPressed(sf::RenderWindow &window);

    void event_polling(sf::RenderWindow &window);

    void renderGame(sf::RenderWindow &window);

    void play();
};


#endif //OOP_GAME_H
