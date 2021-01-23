//
// Created by Rashid on 18.01.2021.
//

#include "Dragon.h"
Dragon::Dragon(int x, int y, std::string sym, std::string hp, std::string damage) {
    this->hp = stoi(hp);
    this->sym_char = sym[0];
    this->damage = stoi(damage);
    this->max_hp = stoi(hp);
    this->x = x;
    this->y = y;
}
res_col Dragon::Collide(Zombie*) {
    return CantMove;
}
res_col Dragon::Collide(Dragon*) {
    return CantMove;
}
res_col Dragon::Collide(AidKit*) {
    return Nothing;
}
res_col Dragon::Collide(Princess*) {
    return CantMove;
}
res_col Dragon::Collide(Knight*) {
    return CanAttack;
}
res_col Dragon::Collide(Floor*) {
    return Nothing;
}
res_col Dragon::Collide(Wall*) {
    return Nothing;
}
res_col Dragon::Collide(Projectile*) {
    return Damage;
}
res_col Dragon::Collide(Gameobject* buf) {
    return buf->Collide(this);
}