//
// Created by Rashid on 18.01.2021.
//

#include "Knight.h"

Knight::Knight(int x, int y) {
    this->hp=100;
    this->sym_char='K';
    this->damage=5;
    this->max_hp=100;
    this->x = x;
    this->y = y;
    this->vision = 3;
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
