//
// Created by Rashid on 18.01.2021.
//

#include "Zombie.h"

Zombie::Zombie(int x, int y, std::string sym, std::string hp, std::string damage){
    this->hp = stoi(hp);
    this->sym_char = sym[0];
    this->damage = stoi(damage);
    this->max_hp = stoi(hp);
    this->x = x;
    this->y = y;
}
void Zombie:: move(int x, int y) {
    this->x = x;
    this->y = y;
}
res_col Zombie::Collide(Knight*) {
    return CanAttack;
}
res_col Zombie::Collide(Zombie*) {
    return CantMove;
}
res_col Zombie::Collide(Dragon*) {
    return CantMove;
}
res_col Zombie::Collide(Princess*) {
    return CantMove;
}
res_col Zombie::Collide(AidKit*) {
    return Nothing;
}
res_col Zombie::Collide(Floor*) {
    return Nothing;
}
res_col Zombie::Collide(Wall*) {
    return Nothing;
}
res_col Zombie::Collide(Projectile*) {
    return CanAttack;
}
res_col Zombie::Collide(Gameobject* buf) {
    return buf->Collide(this);
}