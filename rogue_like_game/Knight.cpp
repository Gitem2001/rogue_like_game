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
std::pair<int,int> Knight::try_move(char a){
    int buf_x = this->x;
    int buf_y=this->y;
    if (a=='W'){
           buf_x--;    
    }
    if (a=='S'){
        buf_x++;
    }
    if (a=='A'){
        buf_y--;
    }
    if (a=='D') {
        buf_y++;
    }
    return std::pair<int, int>(buf_x, buf_y);
}
void Knight::move(int x, int y) {
    this->x = x;
    this-> y = y;
}
void Knight::Regeneration() {
    if (this->hp + 30 > this->max_hp) {
        this->hp = this->max_hp;
    }
    else {
        this->hp += 30;
    }
}
res_col Knight::Collide(Zombie*) {
    return CanAttack;
}
res_col Knight::Collide(Knight*) {
    return CantMove;
}
res_col Knight::Collide(Dragon*) {
    return CanAttack;
}
res_col Knight::Collide(Princess*) {
    return CantMove;
}
res_col Knight::Collide(AidKit*){
    return AidHP;
}
res_col Knight::Collide(Floor*) {
    return Nothing;
}
res_col Knight::Collide(Wall*) {
    return Nothing;
}
res_col Knight::Collide(Projectile*) {
    return CanAttack;
}
res_col Knight::Collide(Gameobject* buf) {
    return buf->Collide(this);
}