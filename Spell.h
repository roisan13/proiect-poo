//
// Created by Radu on 4/24/2024.
//

#ifndef OOP_SPELL_H
#define OOP_SPELL_H


#include <string>
#include <random.hpp>
#include <iostream>

class Spell {
private:
    std::string name;
    int baseDamage;
    int critChance, hitChance;

public:
    Spell(std::string name, int baseDamage, int critChance, int hitChance);

    Spell(const Spell &other);

    Spell &operator=(const Spell &other);

    virtual ~Spell();

    [[nodiscard]] int evalDamage(std::string &alertString) const;

    friend std::ostream &operator<<(std::ostream &os, const Spell &spell);

};


#endif //OOP_SPELL_H
