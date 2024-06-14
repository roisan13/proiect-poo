//
// Created by Radu on 4/24/2024.
//

#include "Button.h"
#include <iostream>
#include <locale>
#include <codecvt>

Button::Button(const std::string &t, sf::Font &font, sf::Vector2f size, sf::Color bgColor) {

    text.setCharacterSize(24);
    text.setFont(font);

    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::wstring wide_string = converter.from_bytes(t);
    text.setString(wide_string);

    button.setSize(size);
    button.setFillColor(bgColor);
}

std::ostream &operator<<(std::ostream &os, const Button &button_) {
    os << "text: " << std::string(button_.text.getString());
    return os;
}

void Button::setBackColor(sf::Color color_) {
    button.setFillColor(color_);
}

void Button::setPosition(sf::Vector2f pos) {
    button.setPosition(pos);
    centerText(pos);
}

void Button::drawTo(sf::RenderWindow &window) {
    window.draw(button);
    window.draw(text);
}

bool Button::isHovered(sf::RenderWindow &window) {
    float mouseX = float(sf::Mouse::getPosition(window).x);
    float mouseY = float(sf::Mouse::getPosition(window).y);

    float btnPosX = button.getPosition().x;
    float btnPosY = button.getPosition().y;
    float btnRightMargin = btnPosX + button.getLocalBounds().width;
    float btnDownMargin = btnPosY + button.getLocalBounds().height;

    return (mouseX < btnRightMargin && mouseX > btnPosX && mouseY < btnDownMargin && mouseY > btnPosY);
}

void Button::setTextString(const std::string &t) {
    text.setString(t);
    centerText(button.getPosition());
}

void Button::centerText(sf::Vector2f pos) {
    // center button?!
    float xPos = (pos.x + (button.getLocalBounds().width - text.getLocalBounds().width) / 2);
    float yPos = (pos.y + (button.getLocalBounds().height - text.getLocalBounds().height) / 2) -
                 button.getLocalBounds().height / 16;
    // float yPos = (pos.y + button.getLocalBounds().height / 2) - (text.getLocalBounds().height / 2);

    text.setPosition({xPos, yPos});
}
