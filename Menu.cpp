//
// Created by Radu on 5/12/2024.
//

#include "Menu.h"

void Menu::initMenuComponents() {
    fontAr.loadFromFile("sprites/arial.ttf");

    playerButton = Button("Player vs Player", fontAr, {300, 50}, sf::Color(0, 0, 0, 150));
    computerButton = Button("Player vs Computer", fontAr, {300, 50}, sf::Color(0, 0, 0, 150));

    playerButton.setPosition({500.f, 650.f});
    computerButton.setPosition({500.f, 750.f});

    mainMenuTexture.loadFromFile("sprites/mainMenu.png");
    mainMenuSprite.setTexture(mainMenuTexture);
}

void Menu::checkMouseButtonPressed(sf::RenderWindow &window) {
    if (playerButton.isHovered(window)) {

        auto game = SingletonGame<Game>::getGameInstance();
        game.play();

        window.close();

    }
    if (computerButton.isHovered(window)) {

        try {
            auto game = SingletonGame<pveGame>::getGameInstance();
            game.play();
        }
        catch (attributeError &err) {
            std::cout << "eroare atribut: " << err.what() << "\n";
        }
        catch (gameLogicError &err) {
            std::cout << "eroare game logic: " << err.what() << "\n";
        }
        catch (grahicsError &err) {
            std::cout << "eroare de grafica: " << err.what() << "\n";
        }

        window.close();
    }

}

void Menu::event_polling(sf::RenderWindow &window) {
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
                if (playerButton.isHovered(window)) {
                    playerButton.setBackColor(sf::Color(0, 0, 0, 200));
                } else {
                    playerButton.setBackColor(sf::Color(0, 0, 0, 150));
                }
                if (computerButton.isHovered(window)) {
                    computerButton.setBackColor(sf::Color(0, 0, 0, 200));
                } else {
                    computerButton.setBackColor(sf::Color(0, 0, 0, 150));
                }
                break;
            case sf::Event::MouseButtonPressed:
                checkMouseButtonPressed(window);
            default:
                break;
        }
    }

}

void Menu::render(sf::RenderWindow &window) {
    window.clear(sf::Color::Black);

    window.draw(mainMenuSprite);
    playerButton.drawTo(window);
    computerButton.drawTo(window);

}

void Menu::displayMenu() {
    sf::RenderWindow window(sf::VideoMode(1280, 900), "Lupta Voievozilor");

    /// Do NOT burn the GPU.
    window.setVerticalSyncEnabled(true);

    initMenuComponents();

    while (window.isOpen()) {
        event_polling(window);

        //Render
        render(window);

        //Draw menu
        window.display();
    }

}

Menu &Menu::getMenu() {
    static Menu menu;
    return menu;
}
