//
// Created by Radu on 4/24/2024.
//

#include "Voievod.h"

Voievod::Voievod(std::string name_, int strength_, int healthPoints_, const std::vector<Spell> &spells_) : name(
        std::move(name_)),
                                                                                                           strength(
                                                                                                                   strength_),
                                                                                                           healthPoints(
                                                                                                                   healthPoints_),
                                                                                                           spells(spells_) {}

Voievod::~Voievod() {
    std::cout << "Voievod destroyed";
}

std::ostream &operator<<(std::ostream &os, const Voievod &voievod) {
    os << voievod.name << " strength: " << voievod.strength << " healthPoints: " << voievod.healthPoints << '\n';
    return os;
}

bool Voievod::isAlive() const {
    return (healthPoints > 0);
}

void Voievod::useSpell(unsigned int spellIndex, Voievod &enemy, std::string &alertString) {
    if (spellIndex < spells.size())
        enemy.healthPoints -= spells[spellIndex].evalDamage(alertString);
    else std::cout << "It didn't work: Wrong spellIndex provided!\n";
}

void Voievod::updateHPText(sf::Text &text) const {
    text.setString(std::to_string(healthPoints));

}
