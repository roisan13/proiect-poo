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


// pt clasa SPELL am constructor de copiere, operator=
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

    Spell(const Spell &other) : name(other.name), baseDamage(other.baseDamage), critChance(other.critChance),
                                hitChance(other.hitChance) {
        std::cout << "Constr copiere Spell\n";
    }

    Spell &operator=(const Spell &other) {
        name = other.name;
        baseDamage = other.baseDamage;
        critChance = other.critChance;
        hitChance = other.hitChance;
        std::cout << "operator= copiere Spell\n";
        return *this;
    }


    //Spell &operator=(const Spell &other) = default;

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


    Voievod &operator=(const Voievod &) = default;


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
    sf::Font fontAr;
    sf::Text textHP1, textHP2;
    sf::Text alertText;
    Button btn1V1, btn2V1, btn3V1, btn1V2, btn2V2, btn3V2;
    std::vector<Button> v1buttons, v2buttons;
    unsigned int gameState;
    int clrAlpha;
    bool alertTextShowing;
    std::string alertString;

    void init_voievodtextHP() {
        textHP1.setFont(fontAr);
        textHP2.setFont(fontAr);
        textHP1.setCharacterSize(72);
        textHP2.setCharacterSize(72);
        textHP1.setPosition({600.f, 350.f});
        textHP2.setPosition({600.f, 800.f});
        voievod1.updateHPText(textHP1);
        voievod2.updateHPText(textHP2);
    };

    void init_sprites() {
        // Load the textures for the background
        textureV1.loadFromFile("sprites/MichaelTheBrave.png");
        textureV2.loadFromFile("sprites/VladTheImpaler.png");
        spriteV1.setTexture(textureV1);
        spriteV2.setTexture(textureV2);
        spriteV2.setPosition(0, 450);

        fontAr.loadFromFile("sprites/arial.ttf");
    }

    void init_alertText() {
        alertText.setFont(fontAr);
        alertText.setCharacterSize(60);
        alertText.setFillColor(sf::Color::Red);
        alertText.setString("Alert TEXT!");
    }

    void init_voievodButtons() {

        // Buttons for voievod1
        btn1V1 = Button("Basic Attack", fontAr, {400, 50}, sf::Color::Black);
        btn2V1 = Button("Powerful Attack", fontAr, {400, 50}, sf::Color::Black);
        btn3V1 = Button("Battle of Calugareni", fontAr, {400, 50}, sf::Color::Black);
        btn1V1.setPosition({20.f,25.f});
        btn2V1.setPosition({20.f, 100.f});
        btn3V1.setPosition({20.f, 175.f});
        v1buttons = {btn1V1, btn2V1, btn3V1};


        // Buttons for voievod2
        btn1V2 = Button("Basic Attack", fontAr, {400, 50}, sf::Color::Black);
        btn2V2 = Button("Powerful Attack", fontAr, {400, 50}, sf::Color::Black);
        btn3V2 = Button("Night Attack at Targoviste", fontAr, {400, 50}, sf::Color::Black);

        // de schimbat numerele astea magice la un moment dat!
        btn1V2.setPosition({20.f,450.f+25.f});
        btn2V2.setPosition({20.f, 450.f+100.f});
        btn3V2.setPosition({20.f, 450.f+175.f});
        v2buttons = {btn1V2, btn2V2, btn3V2};
    }


public:

    Game(const Voievod &voievod1, const Voievod &voievod2) : voievod1(voievod1), voievod2(voievod2), gameState(1),
                                                             clrAlpha(0), alertTextShowing(false) {}

    ~Game() {
        std::cout << "\n Game destructor \n";
    }

    void mouseAction(sf::RenderWindow &window, std::vector<Button> buttons, Voievod &voievod, Voievod &voievodAtacat,
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

    void checkMouseButtonPressed(sf::RenderWindow &window) {
        if (gameState == 1) {
            mouseAction(window, v1buttons, voievod1, voievod2, textHP2);

        } else if (gameState == 2) {
            mouseAction(window, v2buttons, voievod2, voievod1, textHP1);
        }
    }



    void event_polling(sf::RenderWindow &window) {
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

    void renderGame(sf::RenderWindow &window) {

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


    void play() {
        sf::RenderWindow window(sf::VideoMode(1280, 900), "Voievozi si Domnitori");

        /// Do NOT burn the GPU.
        window.setVerticalSyncEnabled(true);

        init_sprites();
        init_voievodtextHP();
        init_alertText();
        init_voievodButtons();

        while (window.isOpen()) {
            event_polling(window);

            //Render
            renderGame(window);

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

    std::string specialAttackText = "Battle of Călugăreni";
    sf::String sfTmp = sf::String::fromUtf8(specialAttackText.begin(), specialAttackText.end());
    Spell basicAttack = Spell("Basic Attack", 5, 30, 85);
    Spell powerfulAttack = Spell("Powerful Attack",10, 20, 60);
    Spell voievod1specificAttack = Spell(sfTmp, 15, 20, 25);

    specialAttackText = "Battle of Târgoviște";
    sfTmp = sf::String::fromUtf8(specialAttackText.begin(), specialAttackText.end());
    Spell voievod2specificAttack = Spell(sfTmp, 15, 20, 25);
    Spell voievod3specificAttack = Spell("Vaslui Battle", 15, 20, 25);
    Spell voievod4specificAttack = Spell("Rovine Battle", 15, 20, 25);

    /// std::vector<Spell> basicSpells = {basicAttack, powerfulAttack};

    Voievod v1 = Voievod("Michael The Brave", 89, 30, {basicAttack, powerfulAttack, voievod1specificAttack});
    Voievod v2 = Voievod("Vlad The Impaler", 93, 30, {basicAttack, powerfulAttack, voievod2specificAttack});
    Voievod v3 = Voievod("Stephen the Great", 95, 30, {basicAttack, powerfulAttack, voievod3specificAttack});
    Voievod v4 = Voievod("Mircea the Elder", 94, 30, {basicAttack, powerfulAttack, voievod4specificAttack});

    // std::vector<Voievod> voievozi = {v1, v2, v3, v4};

    Game game = Game(v1, v2);

    game.play();
    //game.play();


    return 0;
}
