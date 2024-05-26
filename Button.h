//
// Created by Radu on 4/24/2024.
//

#ifndef OOP_BUTTON_H
#define OOP_BUTTON_H


#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class Button {
private:
    sf::RectangleShape button;
    sf::Text text;

    void centerText(sf::Vector2f pos);

public:
    Button() = default;

    Button(const std::string &t, sf::Font &font, sf::Vector2f size, sf::Color bgColor);

    friend std::ostream &operator<<(std::ostream &os, const Button &button_);

    void setBackColor(sf::Color color_);

    void setTextString(const std::string &t);

    void setPosition(sf::Vector2f pos);

    void drawTo(sf::RenderWindow &window);

    bool isHovered(sf::RenderWindow &window);

};


#endif //OOP_BUTTON_H
