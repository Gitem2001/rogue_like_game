//
// Created by Rashid on 18.01.2021.
//

#include "Wall.h"

Wall::Wall(int x, int y,std::string sym) {
    this->x = x;
    this->y = y;
    this->sym_char = sym[0];
}
res_col Wall::Collide(Wall*) {
    return CantMove;
}
res_col Wall::Collide(Zombie*) {
    return CantMove;
}
res_col Wall::Collide(Dragon*) {
    return CantMove;
}
res_col Wall::Collide(Princess*) {
    return CantMove;
}
res_col Wall::Collide(AidKit*) {
    return Nothing;
}
res_col Wall::Collide(Floor*) {
    return Nothing;
}
res_col Wall::Collide(Knight*) {
    return CantMove;
}
res_col Wall::Collide(Projectile*) {
    return Destroy;
}