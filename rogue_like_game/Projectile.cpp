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
res_col Projectile::Collide(Zombie*) {
    return Nothing;
}
res_col Projectile::Collide(Projectile*) {
    return Nothing;
}
res_col Projectile::Collide(Dragon*) {
    return Nothing;
}
res_col Projectile::Collide(Princess*) {
    return Nothing;
}
res_col Projectile::Collide(AidKit*) {
    return Nothing;
}
res_col Projectile::Collide(Floor*) {
    return Nothing;
}
res_col Projectile::Collide(Wall*) {
    return Destroy;
}
res_col Projectile::Collide(Knight*) {
    return Nothing;
}
res_col Projectile::Collide(Gameobject* buf) {
    return buf->Collide(this);
}
