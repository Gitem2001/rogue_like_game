//
// Created by Rashid on 18.01.2021.
//

#include "Gameobject.h"
char Gameobject::GetSym() {
    return this->sym_char;
}
void Gameobject::Hit(int damage) {
    this->hp -= damage;
}
float Gameobject::GetHp() {
    return this->hp;
}