//
// Created by Radu on 5/12/2024.
//

#ifndef OOP_MENU_H
#define OOP_MENU_H

#include "Button.h"
#include "pveGame.h"
#include "Exceptions.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class Menu {
private:
    Button playerButton, computerButton;
    sf::Sprite mainMenuSprite;
    sf::Texture mainMenuTexture;
    sf::Font fontAr;

    void initMenuComponents();

public:
    Menu() = default;

    ~Menu() = default;

    void checkMouseButtonPressed(sf::RenderWindow &window);

    void event_polling(sf::RenderWindow &window);

    void render(sf::RenderWindow &window);

    void displayMenu();
};


#endif //OOP_MENU_H
