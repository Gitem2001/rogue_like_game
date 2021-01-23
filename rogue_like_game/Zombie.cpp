//
// Created by Rashid on 18.01.2021.
//

#include "Zombie.h"

Zombie::Zombie(int x, int y) {
    this->hp=20;
    this->sym_char='Z';
    this->damage=5;
    this->max_hp=20;
    this->x = x;
    this->y = y;
}