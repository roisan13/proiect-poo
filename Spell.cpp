//
// Created by Radu on 4/24/2024.
//

#include "Spell.h"

Spell::Spell(std::string name, int baseDamage, int critChance, int hitChance) : name(std::move(name)),
                                                                                baseDamage(baseDamage),
                                                                                critChance(critChance),
                                                                                hitChance(hitChance) {}

Spell::Spell(const Spell &other) : name(other.name), baseDamage(other.baseDamage), critChance(other.critChance),
                                   hitChance(other.hitChance) {
    std::cout << "Constr copiere Spell\n";
}

Spell &Spell::operator=(const Spell &other) {
    name = other.name;
    baseDamage = other.baseDamage;
    critChance = other.critChance;
    hitChance = other.hitChance;
    std::cout << "operator= copiere Spell\n";
    return *this;
}

Spell::~Spell() {
    std::cout << "Spell destroyed";
}

int Spell::evalDamage(std::string &alertString) const {
    if (effolkronium::random_static::get(1, 100) > hitChance) {
        std::cout << "Miss!";
        alertString = "Miss!";
        return 0;

    }

    if (effolkronium::random_static::get(1, 100) > critChance) {
        alertString = "Hit!";
        return baseDamage;
    } else {
        std::cout << "Critical strike! \n";
        alertString = "Critical Strike!";
        return 2 * baseDamage;
    }
}

std::ostream &operator<<(std::ostream &os, const Spell &spell) {
    os << "name: " << spell.name << " baseDamage: " << spell.baseDamage << " critChance: " << spell.critChance << '\n';
    return os;
}
