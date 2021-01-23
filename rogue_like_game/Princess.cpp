//
// Created by Rashid on 18.01.2021.
//

#include "Princess.h"
Princess::Princess(int x, int y, std::string sym, std::string hp, std::string damage) {
    this->hp = stoi(hp);
    this->sym_char = sym[0];
    this->damage = stoi(damage);
    this->max_hp = stoi(hp);
    this->x = x;
    this->y = y;
}
res_col Princess::Collide(Zombie*) {
    return CantMove;
}
res_col Princess::Collide(Princess*) {
    return CantMove;
}
res_col Princess::Collide(Dragon*) {
    return CantMove;
}
res_col Princess::Collide(Knight*) {
    return CantMove;
}
res_col Princess::Collide(AidKit*) {
    return Nothing;
}
res_col Princess::Collide(Floor*) {
    return Nothing;
}
res_col Princess::Collide(Wall*) {
    return Nothing;
}
res_col Princess::Collide(Projectile*) {
    return Damage;
}