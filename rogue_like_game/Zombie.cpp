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