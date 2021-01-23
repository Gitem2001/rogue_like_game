//
// Created by Rashid on 18.01.2021.
//

#include "Knight.h"

Knight::Knight(int x, int y, std::string sym, std::string hp, std::string damage, std::string vision) {
    this->hp = stoi(hp);
    this->sym_char = sym[0];
    this->damage = stoi(damage);
    this->max_hp = stoi(hp);
    this->x = x;
    this->y = y;
    this->vision = stoi(vision);
}
void Knight::Move(char a,Map map_){
    if (a=='W'){
        this->x--;
    }
    if (a=='S'){
        this->x++;
    }
    if (a=='A'){
        this->y--;
    }
    if (a=='D') {
        this->y++;
    }
}
