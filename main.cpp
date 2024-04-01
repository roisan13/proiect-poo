#include <iostream>
#include <array>
#include <chrono>
#include <thread>

#include <random.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

//////////////////////////////////////////////////////////////////////
/// NOTE: this include is needed for environment-specific fixes     //
/// You can remove this include and the call from main              //
/// if you have tested on all environments, and it works without it //
#include "env_fixes.h"                                              //
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
/// This class is used to test that the memory leak checks work as expected even when using a GUI
/*
class SomeClass {
public:
    explicit SomeClass(int) {}
};

SomeClass *getC() {
    return new SomeClass{2};
}
 */
//////////////////////////////////////////////////////////////////////

class Voievod;

class Button{
private:
    sf::RectangleShape button;
    sf::Text text;

public:
    Button()= default;

    Button(const std::string& t, sf::Font &font, sf::Vector2f size, sf::Color bgColor){

        text.setString(t);
        text.setCharacterSize(24);
        text.setFont(font);

        button.setSize(size);
        button.setFillColor(bgColor);
    }

    friend std::ostream &operator<<(std::ostream &os, const Button &button_) {
        os << "text: " << std::string(button_.text.getString());
        return os;
    }

    void setBackColor(sf::Color color_){
        button.setFillColor(color_);
    }

    /*
    void setTextColor(sf::Color color_){
        text.setFillColor(color_);
    }

    void setFont(sf::Font &font){
        text.setFont(font);
    }
     */

    void setPosition(sf::Vector2f pos){
        button.setPosition(pos);

        // center button?!
        float xPos = (pos.x + button.getLocalBounds().width / 2) - (text.getLocalBounds().width / 2);
        float yPos = (pos.y + button.getLocalBounds().height / 2) - (text.getLocalBounds().height / 2);

        text.setPosition({xPos, yPos});
    }

    void drawTo(sf::RenderWindow &window) {
        window.draw(button);
        window.draw(text);
    }

    bool isHovered(sf::RenderWindow &window) {
        float mouseX = float(sf::Mouse::getPosition(window).x);
        float mouseY = float(sf::Mouse::getPosition(window).y);

        float btnPosX = button.getPosition().x;
        float btnPosY = button.getPosition().y;
        float btnRightMargin = btnPosX + button.getLocalBounds().width;
        float btnDownMargin = btnPosY + button.getLocalBounds().height;

        return (mouseX < btnRightMargin && mouseX > btnPosX && mouseY < btnDownMargin && mouseY > btnPosY);
    }

};
class Spell{
private:
    std::string name;
    int baseDamage;
    int critChance;  // critchance/100
    int hitChance;

public:
    Spell(std::string name, int baseDamage, int critChance, int hitChance) : name(std::move(name)), baseDamage(baseDamage),
                                                                             critChance(critChance),
                                                                             hitChance(hitChance) {}


    virtual ~Spell(){
        std::cout << "Spell destroyed";
    }

    [[nodiscard]] int evalDamage(std::string &alertString) const{
        if ( effolkronium::random_static::get(1, 100) > hitChance) {
            std::cout << "Miss!";
            alertString = "Miss!";
            return 0;

        }

        if ( effolkronium::random_static::get(1, 100) > critChance) {
            alertString = "Hit!";
            return baseDamage;
        }
        else {
            std::cout << "Critical strike! \n";
            alertString = "Critical Strike!";
            return 2 * baseDamage;
        }
    }


    friend std::ostream &operator<<(std::ostream &os, const Spell &spell) {
        os << "name: " << spell.name << " baseDamage: " << spell.baseDamage << " critChance: " << spell.critChance << '\n';
        return os;
    }

};

/// class VoievodAttack : public Spell{};

class Voievod {
private:
    std::string name;
    int strength;
    int healthPoints;
    std::vector<Spell> spells;

public:
    Voievod(std::string name_, int strength_, int healthPoints_, const std::vector<Spell> &spells_) : name(std::move(name_)),
                                                                                                      strength(
                                                                                                              strength_),
                                                                                                      healthPoints(
                                                                                                              healthPoints_),
                                                                                                      spells(spells_) {}

    virtual ~Voievod(){
        std::cout << "Voievod destroyed";
    }


    Voievod& operator=(const Voievod&) = default;



    friend std::ostream &operator<<(std::ostream &os, const Voievod &voievod) {
        os << voievod.name << " strength: " << voievod.strength << " healthPoints: " << voievod.healthPoints << '\n';
        return os;
    };

    /*
    void printSpells(){
        for (unsigned int i = 0; i < spells.size(); ++i)
            std::cout << i + 1 << ". " << spells[i] << '\n';
    }
     */

    [[nodiscard]] bool isAlive() const{
        return (healthPoints > 0);
    }
    void updateHPText(sf::Text &text) const{
        text.setString(std::to_string(healthPoints));

    }

    void useSpell(unsigned int spellIndex, Voievod& enemy, std::string &alertString){
        if ( spellIndex < spells.size() )
            enemy.healthPoints -= spells[spellIndex].evalDamage(alertString);
        else std::cout << "It didn't work: Wrong spellIndex provided!\n";
    }
};

class Game{
private:
    Voievod voievod1, voievod2;
    sf::Sprite spriteV1, spriteV2;
    sf::Texture textureV1, textureV2;


public:
    void start(){
        sf::RenderWindow window(sf::VideoMode(1280, 900), "Voievozi si Domnitori");
        sf::Event ev{};
        sf::Font fontAr;
        sf::Text textHP1, textHP2;
        sf::Text alertText;

        /// Do NOT burn the GPU.
        window.setVerticalSyncEnabled(true);

        unsigned int gameState;
        // alpha for the alert text
        int clrAlpha = 0;
        bool alertTextShowing;

        fontAr.loadFromFile("sprites/arial.ttf");


        // Text for voievod1 and voievod2 HEALTH POINTS

        textHP1.setFont(fontAr);
        textHP2.setFont(fontAr);
        textHP1.setCharacterSize(72);
        textHP2.setCharacterSize(72);
        textHP1.setPosition({600.f,350.f});
        textHP2.setPosition({600.f,800.f});
        voievod1.updateHPText(textHP1);
        voievod2.updateHPText(textHP2);


        // Load the textures for the background

        textureV1.loadFromFile("sprites/MichaelTheBrave.png");
        textureV2.loadFromFile("sprites/VladTheImpaler.png");
        spriteV1.setTexture(textureV1);
        spriteV2.setTexture(textureV2);
        spriteV2.setPosition(0, 450);


        // Alert text

        alertText.setFont(fontAr);
        alertText.setCharacterSize(60);
        alertText.setFillColor(sf::Color::Red);
        alertText.setString("Alert TEXT!");
        std::string alertString;


        // Buttons for voievod1

        Button btn1V1("Basic Attack",fontAr, {400, 50}, sf::Color::Black);
        Button btn2V1("Powerful Attack",fontAr,{400, 50}, sf::Color::Black);
        Button btn3V1("Battle of Calugareni",fontAr, {400, 50}, sf::Color::Black);
        btn1V1.setPosition({20.f,25.f});
        btn2V1.setPosition({20.f, 100.f});
        btn3V1.setPosition({20.f, 175.f});
        std::vector<Button> v1buttons = {btn1V1,btn2V1,btn3V1};


        // Buttons for voievod2

        Button btn1V2("Basic Attack",fontAr, {400, 50}, sf::Color::Black);
        Button btn2V2("Powerful Attack",fontAr,{400, 50}, sf::Color::Black);
        Button btn3V2("Night Attack at Targoviste",fontAr, {400, 50}, sf::Color::Black);
        btn1V2.setPosition({20.f,450.f+25.f});
        btn2V2.setPosition({20.f, 450.f+100.f});
        btn3V2.setPosition({20.f, 450.f+175.f});
        std::vector<Button> v2buttons = {btn1V2,btn2V2,btn3V2};

        gameState = 1;
        alertTextShowing = false;
        while (window.isOpen())
        {
            //Event polling
            while (window.pollEvent(ev)){

                switch (ev.type){
                    case sf::Event::Closed:
                        window.close();
                        break;
                    case sf::Event::KeyPressed:
                        if (ev.key.code == sf::Keyboard::Escape)
                            window.close();
                        break;
                    case sf::Event::MouseMoved:
                        for (auto & v1button: v1buttons)
                            if (v1button.isHovered(window)){
                                v1button.setBackColor(sf::Color::Red);
                            }
                            else{
                                v1button.setBackColor(sf::Color::Black);
                            }
                        for (auto & v2button: v2buttons)
                            if (v2button.isHovered(window)){
                                v2button.setBackColor(sf::Color::Red);
                            }
                            else{
                                v2button.setBackColor(sf::Color::Black);
                            }
                        break;
                    case sf::Event::MouseButtonPressed:
                        std::cout << " Buton mouse apasat\n";
                        if (gameState == 1) {
                            for (unsigned int i = 0; i < v1buttons.size(); ++i)
                                if (v1buttons[i].isHovered(window)) {
                                    /// CHECK IF IT IS CORRECT ROUND!!!
                                    /// PLAY AUDIO!!!!
                                    voievod1.useSpell(i, voievod2, alertString);
                                    voievod2.updateHPText(textHP2);

                                    alertTextShowing = true;
                                    alertText.setString(alertString);
                                    gameState = 2;
                                }
                        }
                        else if (gameState == 2) {
                            for (unsigned int i = 0; i < v2buttons.size(); ++i)
                                if (v2buttons[i].isHovered(window)) {
                                    /// CHECK IF IT IS CORRECT ROUND!!!
                                    /// PLAY AUDIO!!!!
                                    voievod2.useSpell(i, voievod1, alertString);
                                    voievod1.updateHPText(textHP1);

                                    alertTextShowing = true;
                                    alertText.setString(alertString);
                                    gameState = 1;
                                }
                        }
                    default:
                        break;
                }
            }

            //Update

            //Render
            window.clear(sf::Color::Black); //Clear old frame

            if (alertTextShowing){
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



            for (auto & button: v1buttons)
                button.drawTo(window);
            for (auto & button: v2buttons)
                button.drawTo(window);

            //Draw your game
            window.display(); //Tell app that window is done drawing

            if(!(voievod1.isAlive() && voievod2.isAlive())){
                gameState = 0;
            }

        }

        if (voievod1.isAlive() && !voievod2.isAlive())
            std::cout << "Voievod 1 - winner!\n";
        else if (!voievod1.isAlive() && voievod2.isAlive())
            std::cout << "Voievod 2 - winner!\n";
        else std::cout <<"It's a tie!\n";
    }

    /*

     ///
     ///    OLD CONSOLE IMPLEMENTATION
     ///

    void play(){
        std::cout << "The game has started! \n";
        std::cout << "Voievod 1: " << voievod1 << "\n" << "Voievod 2: " <<  voievod2 << "\n";

        while(voievod1.isAlive() && voievod2.isAlive()){

            std::cout << "Voievod1, choose your spell:\n";
            voievod1.printSpells();
            int *spellIndex_ = new int;
            std::cin >> *spellIndex_;
            // aici ar trebui un if in care sa se citeasca frumos spellIndex, fara erori
            voievod1.useSpell(*spellIndex_-1, voievod2,);
            std::cout << "It worked! " << voievod2;

            std::cout << "Voievod2, choose your spell:\n";
            voievod2.printSpells();
            std::cin >> *spellIndex_;
            // alt if frumos, posibil o functie
            voievod2.useSpell(*spellIndex_-1, voievod1);
            std::cout << "It worked! " << voievod1;

            delete spellIndex_;

        }

    };
     */

    Game(const Voievod &voievod1, const Voievod &voievod2) : voievod1(voievod1), voievod2(voievod2) {}

    virtual ~Game() {
        std::cout << "\nGame over! \n";
    }
};


int main() {
    ////////////////////////////////////////////////////////////////////////
    /// NOTE: this function call is needed for environment-specific fixes //
    init_threads();                                                       //
    ////////////////////////////////////////////////////////////////////////

    /*

    SomeClass *c = getC();
    std::cout << c << "\n";
    delete c;

    */


    Spell basicAttack = Spell("Basic Attack", 5, 30, 85);
    Spell powerfulAttack = Spell("Powerful Attack",10, 20, 60);
    Spell voievod1specificAttack = Spell("Battle of Calugareni", 15, 20, 25);
    Spell voievod2specificAttack = Spell("Night Attack at Targoviste", 15, 20, 25);
    Spell voievod3specificAttack = Spell("Vaslui Battle", 15, 20, 25);
    Spell voievod4specificAttack = Spell("Rovine Battle", 15, 20, 25);

    /// std::vector<Spell> basicSpells = {basicAttack, powerfulAttack};

    Voievod v1 = Voievod("Michael The Brave", 89, 30, {basicAttack, powerfulAttack, voievod1specificAttack});
    Voievod v2 = Voievod("Vlad The Impaler", 93, 30, {basicAttack, powerfulAttack, voievod2specificAttack});
    Voievod v3 = Voievod("Stephen the Great", 95, 30, {basicAttack, powerfulAttack, voievod3specificAttack});
    Voievod v4 = Voievod("Mircea the Elder", 94, 30, {basicAttack, powerfulAttack, voievod4specificAttack});

    // std::vector<Voievod> voievozi = {v1, v2, v3, v4};

    Game game = Game(v1, v2);

    game.start();
    //game.play();

    /*
    sf::RenderWindow window;
    ///////////////////////////////////////////////////////////////////////////
    /// NOTE: sync with env variable APP_WINDOW from .github/workflows/cmake.yml:31
    window.create(sf::VideoMode({800, 700}), "My Window", sf::Style::Default);
    ///////////////////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////////////////
    /// NOTE: mandatory use one of vsync or FPS limit (not both)            ///
    /// This is needed so we do not burn the GPU                            ///
    window.setVerticalSyncEnabled(true);                            ///
    /// window.setFramerateLimit(60);                                       ///
    ///////////////////////////////////////////////////////////////////////////

    while(window.isOpen()) {
        bool shouldExit = false;
        sf::Event e{};
        while(window.pollEvent(e)) {
            switch(e.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                std::cout << "New width: " << window.getSize().x << '\n'
                          << "New height: " << window.getSize().y << '\n';
                break;
            case sf::Event::KeyPressed:
                std::cout << "Received key " << (e.key.code == sf::Keyboard::X ? "X" : "(other)") << "\n";
                if(e.key.code == sf::Keyboard::Escape)
                    shouldExit = true;
                break;
            default:
                break;
            }
        }
        if(shouldExit) {
            window.close();
            break;
        }
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(300ms);

        window.clear();
        window.display();
    }
     */
    return 0;
}
