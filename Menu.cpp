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

        std::string specialAttackText = "Battle of Călugăreni";
        sf::String sfTmp = sf::String::fromUtf8(specialAttackText.begin(), specialAttackText.end());
        Spell basicAttack = Spell("Basic Attack", 5, 30, 85);
        Spell powerfulAttack = Spell("Powerful Attack", 10, 20, 60);
        Spell voievod1specificAttack = Spell(sfTmp, 15, 20, 25);

        specialAttackText = "Battle of Târgoviște";
        sfTmp = sf::String::fromUtf8(specialAttackText.begin(), specialAttackText.end());
        Spell voievod2specificAttack = Spell(sfTmp, 15, 20, 25);


        Voievod v1 = Voievod("Michael The Brave", 89, 30, {basicAttack, powerfulAttack, voievod1specificAttack});
        Voievod v2 = Voievod("Vlad The Impaler", 93, 30, {basicAttack, powerfulAttack, voievod2specificAttack});

        Game game = Game(v1, v2);
        game.play();

        window.close();

    }
    if (computerButton.isHovered(window)) {

        try {
            pveGame game = pveGame();
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
