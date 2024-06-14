//
// Created by Radu on 4/24/2024.
//

#ifndef OOP_VOIEVOD_H
#define OOP_VOIEVOD_H

#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics/Text.hpp>
#include "Spell.h"

class Voievod {
private:
    std::string name;
    int strength{};
    int healthPoints{};
    std::vector<Spell> spells;

public:
    Voievod() = default;

    Voievod(std::string name_, int strength_, int healthPoints_, const std::vector<Spell> &spells_);

    virtual ~Voievod();

    Voievod &operator=(const Voievod &) = default;

    friend std::ostream &operator<<(std::ostream &os, const Voievod &voievod);

    [[nodiscard]] bool isAlive() const;

    void updateHPText(sf::Text &text) const;

    void useSpell(unsigned int spellIndex, Voievod &enemy, std::string &alertString);
};


#endif //OOP_VOIEVOD_H
