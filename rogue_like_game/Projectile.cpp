//
// Created by Rashid on 20.01.2021.
//

#include "Projectile.h"

Projectile::Projectile(int x, int y,std::pair<int,int> dir) {
    this->x = x;
    this->y = y;
    this->sym_char ='*';
    this->direction = dir;
    this->damage = 20;
}
void Projectile::Fly() {
    this->x += this->direction.first;
    this->y += this->direction.second;
}
res_col Projectile::Collide(Zombie*) {
    return CantMove;
}
res_col Projectile::Collide(Projectile*) {
    return Destroy;
}
res_col Projectile::Collide(Dragon*) {
    return CantMove;
}
res_col Projectile::Collide(Princess*) {
    return CantMove;
}
res_col Projectile::Collide(AidKit*) {
    return Destroy;
}
res_col Projectile::Collide(Floor*) {
    return Nothing;
}
res_col Projectile::Collide(Wall*) {
    return Destroy;
}
res_col Projectile::Collide(Knight*) {
    return CantMove;
}
res_col Projectile::Collide(Gameobject* buf) {
    return buf->Collide(this);
}
