//
// Created by Rashid on 20.01.2021.
//

#include "Projectile.h"

Projectile::Projectile(int x, int y) {
    this->x = x;
    this->y = y;
    this->sym_char ='*';
}
void Projectile::Fly(int x_goal, int y_goal) {
    if (x<x_goal){
        x++;
    }else if (x>x_goal){
        x--;
    }
    if (y<y_goal){
        y++;
    }else if (y>y_goal){
        y--;
    }
}